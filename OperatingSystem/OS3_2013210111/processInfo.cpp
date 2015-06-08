#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <fstream>
struct ProcessInformation
{
	unsigned int 	pid;
	std::string 	name;
	unsigned long 	virtualMemorySize;
	unsigned long 	physicsMemorySize;
	unsigned long 	sharedMemorySize;
	unsigned long	prevPhysicsMemorySize;
	int				signDisplayCount;

	ProcessInformation()
		: pid(0), name(""), virtualMemorySize(0),
		prevPhysicsMemorySize(0), sharedMemorySize(0),
		physicsMemorySize(0), signDisplayCount(0)
	{	}

	bool IsWorkingSetChanged()
	{
		return prevPhysicsMemorySize != physicsMemorySize;
	}	
};
int main()
{
	DIR* dp = NULL;
	std::map<unsigned int, ProcessInformation*> processInformationMap;
	
	


	struct dirent* entry = NULL;
	bool isFirst = true;
	while(true)
	{
		// Proc Directory를 열고
		dp = opendir("/proc/");
		if(dp == NULL)
		{
			printf("[Error : open /proc/ error\n");
			continue;
		}
		// 모든 Entry들을 순회하고
		while( ( entry = readdir(dp)) != NULL)
		{
			struct stat buf;

			lstat(entry->d_name, &buf);

			// 우리가 찾는 것은 폴더이며,
			if( S_ISDIR(buf.st_mode))
			{
				// 폴더의 이름은 PID꼴이어야 하고(정수)
				unsigned int pid = atoi(entry->d_name);
				
				if(pid == 0)
					continue;

				std::string dirStr = "/proc/";
				dirStr.append(entry->d_name, entry->d_reclen);
				
				
				ProcessInformation* pi;
				
				// 새로운 프로세스면 새로 할당하고
				if(processInformationMap.find(pid) == processInformationMap.end())
				{
					pi = new ProcessInformation();
					
					// /proc/PID/stat 에서 프로세스 이름을 찾고
					std::string statStr;
					statStr.append(dirStr.c_str());
					statStr.append("/stat");
					FILE* fin = fopen(statStr.c_str(), "r");
					if(fin == NULL)
					{
						printf("[Error] Open Fail - %s\n", statStr.c_str());
					}
					else
					{
						char buf[64] = "";
						fscanf(fin, "%d %s",&pi->pid, buf);
						pi->name = buf;
					}
					fclose(fin);

					// Map에 추가하고
					processInformationMap.insert(std::pair<unsigned int, ProcessInformation*>(pid, pi));
				}
				else	// 이미 이쓴 프로세스면 가져오고
				{
					pi = processInformationMap[pid];
				}

				// 메모리 정보가 담겨있는 /proc/PID/statm 을 열어서
				std::string statmStr = dirStr.c_str();
				statmStr.append("/statm");
				std::ifstream statmIfs(statmStr.c_str());
				if(statmIfs.is_open() == false)
				{
					printf("[Error] Open Fail - %s\n", statmStr.c_str());
				}
				else
				{
					// 데이터들을 업데이트.
					pi->prevPhysicsMemorySize = pi->physicsMemorySize;

					statmIfs >> pi->virtualMemorySize
					>> pi->physicsMemorySize
					>> pi->sharedMemorySize;
					if(pi->IsWorkingSetChanged())
						pi->signDisplayCount = 2;
				}
				statmIfs.close();
			}
		}
		
		printf("PID\tName\tVirtual\tPhysics\tShared\tWSS\n");
		for(std::map<unsigned int, ProcessInformation*>::iterator it = processInformationMap.begin();
			it != processInformationMap.end();
			++it)
		{
			printf("%d\t%s\t%d\t%d\t%d\t%c\n", it->second->pid,
				it->second->name.c_str(),
				it->second->virtualMemorySize * 4,
				it->second->physicsMemorySize * 4,
				it->second->sharedMemorySize * 4,
				it->second->signDisplayCount > 0 & !isFirst ? '*' : ' ');
			--it->second->signDisplayCount;
		}

		isFirst = false;
		closedir(dp);
		usleep(50 * 1000);
	}

	
	

	for(std::map<unsigned int, ProcessInformation*>::iterator it = processInformationMap.begin();
		it != processInformationMap.end();
		++it)
		delete(it->second);
}