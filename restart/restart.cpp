#include"restart.h"
void ReverChar(const char* arr,char* out){
   

    int len=strlen(arr);
    for(int i=0;i<len;i++){
        out[i]=arr[len-i-1];
    }
    out[len]='\0';
    
}
std::string GetStrinG(char *arr, int startindex, int size)
{
    char *text = (char *)malloc(size+1);
    memcpy(text, arr + startindex, size);
    text[size]='\0';
    std::string t=std::move(text);
    return t;
}
int SearchWordIndex(char *arr, int startindex, int size, int count, const char *search)
{
    int len = strlen(search);
    int c = 0;
    
    if (startindex > size)
    {
        char s[100];
        ReverChar(search,s);
        for (int i = startindex; i >= size; i--)
        {
            for (int j = i; j >= size; j--)
            {
                if (arr[j] == s[i-j])
                {
                    if (i-j == len - 1)
                    {
                        c++;
                        if (c == count)
                            return i;
                    }
                }
                else
                {
                    i -= i-j;
                    break;
                }
            }
        }
    }
    else
    {
        for (int i = startindex; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                if (arr[j] == search[j - i])
                {
                    if (j - i == len - 1)
                    {
                        c++;
                        if (c == count)
                            return i;
                    }
                }
                else
                {
                    i += j - i;
                    break;
                }
            }
        }
        return -1;
    }
}
void StartProgram(){
#ifdef _WIN32
    system("AZS.exe");
#else
    system("./AZS");
#endif
    
}


void ShowPid(PID* pid){
 std::wcout<<"PID: "<<pid->pid<<" PWD: "<<pid->pwd<<" NAME: "<<pid->nameprogram<<" PWD DIR: "<<pid->pwddir<<"\n";
}
#ifdef __linux__ 
std::vector<PID> GetAllProc(){

    DIR *dir; struct dirent *diread;
    vector<PID> pids;
    if ((dir = opendir("/proc")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            PID pid;
            
            if(atoi(diread->d_name)!=0){
                pid.pid=atoi(diread->d_name);
                pids.push_back(pid);
            }
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return pids;
    }
    
    return std::move(pids);
}
std::string GetPwdProc(const char* path) {

    std::ifstream f;
    std::string read;
    f.open(path, std::ios_base::in);
    if (f.is_open()) {

        f >> read;
        f.close();
    }
    return read;
}
#endif
std::vector<PID> FindProc(){
    wchar_t mypwd[300];
    
     std::vector<PID> find;
#ifdef _WIN32
     GetModuleFileNameW(NULL, mypwd, MAX_PATH);
     PROCESSENTRY32 entry;
     entry.dwSize = sizeof(PROCESSENTRY32);

     HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

     if (Process32First(snapshot, &entry) == TRUE)
     {
         while (Process32Next(snapshot, &entry) == TRUE)
         {
             if (wcscmp(entry.szExeFile, L"AZS.exe") == 0)
             {
                 PID pid;
                 pid.pid = entry.th32ProcessID;
                 MODULEENTRY32 ModEntry = { 0 };
                 ModEntry.dwSize = sizeof(ModEntry);
                 Module32First(snapshot, &ModEntry);
                 pid.pwd = ModEntry.szExePath;
                 find.push_back(pid);
                 break;
             }
         }
     }

     CloseHandle(snapshot);
#else
     getcwd(mypwd, 300);
     std::vector<PID>pids = GetAllProc();

     for (int i = 0; i < pids.size(); i++) {

         std::string path = "/proc/" + std::to_string(pids[i].pid) + "/cmdline";
         std::string pwd = GetPwdProc(path.c_str());
         pids[i].pwd = pwd;
         int startname = SearchWordIndex(&pwd[0], pwd.length(), 0, 1, "/");
         if (startname != -1) {
             pids[i].nameprogram = GetStrinG(&pwd[startname + 1], 0, pwd.length() - startname - 1);
             pids[i].pwddir = GetStrinG(&pwd[0], 0, startname);
         }
         //ShowPid(&pids[i]);

     }


     for (int i = 0; i < pids.size(); i++) {
         if (pids[i].nameprogram == "AZS") {
             find.push_back(pids[i]);

         }
     }
#endif
   
    std::cout<<"MY PWD: "<<mypwd<<"\n";
    return find;
}
void KillProc(int pid) {
#ifdef _WIN32
#else
    kill(pid, 9);
#endif
}
int main(){
    std::vector<PID> azs=FindProc();
    for(int i=0;i<azs.size();i++){
        KillProc(azs[i].pid);
    }
    StartProgram();
    return 0;
}