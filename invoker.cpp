#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <thread>
#include <chrono>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

namespace logging{
    
    void exec() {
            
            // Create Record
            
            // Temperature Sensor    
            
            pid_t pid_sensor_write = fork();
    
            if (pid_sensor_write==0) { 
                //std::cout << "heres\n"; 
                char *argv_sensor[]={"sudo", "-s77","-dw", "-ib","-c2500", "1", "0x00", "" ,NULL};
                execv("log_system",argv_sensor);
            } else { 
                //std::cout << "hedddre\n"; 
                waitpid(pid_sensor_write,0,0); 
            }
                
            pid_t pid_sensor_read = fork();
                
            if (pid_sensor_read==0) { 
                char *argvector_sensor[]={"sudo", "-s77","-dr", "-ib", "-c2500", "1", NULL};
                execv("log_system",argvector_sensor);
            } else { 
                waitpid(pid_sensor_read,0,0); 
            }
            
            //std::this_thread::sleep_for(std::chrono::seconds(5));
            
            // Clock
            
            pid_t pid_clock_write = fork();
    
            if (pid_clock_write==0) { 
                char *argv[]={"sudo", "-s104","-dw", "-ib", "1", "0x00", "" ,NULL};
                execv("log_system",argv);
            } else { 
                waitpid(pid_clock_write,0,0); 
            }
                
            pid_t pid_clock_read =fork();
                
            if (pid_clock_read==0) { 
                char *argvector[]={"sudo", "-s104","-dr", "-ib", "7", NULL};
                execv("log_system",argvector);
            } else { 
                waitpid(pid_clock_read,0,0); 
            }
    
    }
    
    void run() {
        
        while(true) {
            
            std::ofstream PollingFile("polling_state.txt");
            
            PollingFile << 0;
            
            PollingFile.close();
            
            exec();
                
                
            // Sleep & Poll for High Temperature
            
            for(int i = 0; i < 10; i++){
                
                std::ofstream PollingFile("polling_state.txt");
            
                PollingFile << 1;
            
                PollingFile.close();
                
                exec();
                
                // Sleep for 100 miliseconds
                std::this_thread::sleep_for(std::chrono::seconds(1));  
            }
            
            
        }
        
    } //Log seconds
    
    
    
}

int main()
{
    
    std::ofstream LogFile("log.txt");
            
    LogFile << "";
            
    LogFile.close();
    
    // Inital Value
            
    std::ofstream RecordFile("record.txt");
            
    RecordFile << 0;
            
    RecordFile.close();
    
    logging::run();
    
    return 0;
}
