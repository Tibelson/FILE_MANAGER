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

        

};
void list_directory(const char* path){
            Directory_handle dh(path);
            DIR* d = dh.get_ptr();

          
            struct dirent* entry;

           while((entry = readdir(d)) != NULL){

            if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name, "..")==0){
                continue;
            }

            char fullpath[PATH_MAX];

            snprintf(fullpath, sizeof(fullpath),"%s/%s",path,entry->d_name);
            
            struct stat st;
            
            if(lstat(fullpath,&st) == -1){
                std::cerr << "path error " << strerror(errno) << std::endl;
                continue;
            }
             if(S_ISDIR(st.st_mode)){
                    std::cout << "[DIR] " << entry->d_name<<" || "<< st.st_size << " bytes." << std::endl;
                }
                else if(S_ISREG(st.st_mode)){
                    std::cout << "[FILE] " << entry->d_name<<" || "<< st.st_size << " bytes." <<std::endl;

                }
                else if (S_ISLNK(st.st_mode)){
                    std::cout << "[LINK] "<< entry->d_name<< " || " <<st.st_size<<" bytes\n";
                }
                else std::cout << "Other\n";
           }
        //    Directory_handle f(path);
        }
int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Usage: filepath error\n";

        return 1;
    }
    try{
        list_directory(argv[1]);
    }
    catch(const std::exception &e){
        std::cerr << "Error " << e.what() << "\n";
    }
    
}