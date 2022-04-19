# code_netp

`csapp_netp_win.h`是`csapp.h`的替代

`csapp_netp_win.c`是`csapp.c`的替代



## 编译指南（gcc）

```powershell
gcc hostinfo_win.c -o hostinfo -lws2_32

gcc echoserveri_win.c echo_win.c csapp_netp_win.c -o echoserveri -lws2_32
gcc echoclient_win.c csapp_netp_win.c -o echoclient -lws2_32
```



## 替换内容

 * ws2def.h
    * ADDRINFOA <= struct addrinfo
 * ws2tcpip.h
    * GetAddrInfo <= getaddrinfo
    * GetNameInfo <= Getnameinfo
    * FreeAddrInfo <= Freeaddrinfo
 * csapp.h
    * closesocket <= Close（去除warp）
    * windows_error <= unix_error
    * recv <= read（win不支持）
    * send <= fwrite（win不支持）
    * fgets <= Fgets（去除warp）
    * fputs <= Fputs（去除warp）

