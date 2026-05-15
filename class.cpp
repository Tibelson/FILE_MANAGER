#include <iostream>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
class Directory_handle{
   private:
        DIR* d = nullptr;
    public:
        Directory_handle(const char* dir){

            d = opendir(dir);
            if(d == nullptr){
                throw std::runtime_error(std::string("opendir failed. ") + strerror(errno));

           } 
           
        }
        ~Directory_handle(){
            if(d != nullptr)
            
            closedir(d);
        }
        DIR* get_ptr() const{
            return d;
        }
        Directory_handle(const Directory_handle&) = delete;
        Directory_handle& operator=(const Directory_handle&) = delete;

        void list_directory(const char* path){
            DIR* d = opendir(path);
            if(!d){
                throw std::runtime_error(std::string("opendir failed. ") + strerror(errno));
            }
            struct dirent* entry;

           while((entry = readdir(d)) != NULL){

            char fullpath[PATH_MAX];

            snprintf(fullpath, sizeof(fullpath),"%s/%s",path,entry->d_name);
            
            struct stat st;
            
            if(lstat(fullpath,&st) == -1){
                continue;
            }
             if(S_ISDIR(st.st_mode)){
                    std::cout << "[DIR] " << entry->d_name << std::endl;
                }
                else if(S_ISREG(st.st_mode)){
                    std::cout << "[FILE] " << entry->d_name <<std::endl;

                }
                else if (S_ISLNK(st.st_mode)){
                    std::cout << "[LINK]\n";
                }
                else std::cout << "Other\n";
           }
           closedir(d);
        }

};