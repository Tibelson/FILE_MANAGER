#include <iostream>
#include <dirent.h>
#include <cstring>
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