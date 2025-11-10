# brick-breaker
Second year IT Bachelor group project  : create a brick breaker game with C++ and SMFL

## Stack:
- C++ 
- SFML ( `#include <SFML/Graphics.hpp>` )
- Docker

## Installs
If you're on windows, you'll need a software to get the GUI working. On linux X server does the job, on linux you can either download and install `VcXsrv` or `Xming`. For this project, we'll be using `VcXsrv` on windows

## On Windows
## 1. Install VcXsrv
### 1.1 Download VcXsrv from [https://vcxsrv.com/](https://vcxsrv.com/) or [https://github.com/marchaesen/vcxsrv](https://github.com/marchaesen/vcxsrv)
Download `vcxsrv-64.21.1.16.1.installer.exe`
Typical installation is fine (all components checked).
### 1.2 Configure and start VcXsrv
- Open XLaunch (installed with VcXsrv).
- Choose **“Multiple windows”** (so each SFML window appears separately).
- Display settings: **“Start no client”** (we just want to display Docker windows).

Extra settings:
- Check: **“Disable access control”** : ⚠️ this is important so Docker can connect without extra authentication.

Leave the rest as default.
Finish and start the server. You should see an X icon in your system tray.

If needed, you can use `config.xlaunch` where all config were saved.
### 1.3 Add environment configuration to docker-compose.yml
```
- DISPLAY=host.docker.internal:0
```

## 2. Set environment variable on powershell or CMD
⚠️ Set this environment variable on your host !!
```bash
set DISPLAY=host.docker.internal:0
```
or in WSL2
```bash
export DISPLAY=$(ip route | awk '/default/ {print $3}'):0
```

## 3. Build image
```bash
docker compose up --build -d
```
if image already build:
```bash
docker compose up
```

## 4. Sanity checks
```bash
docker compose exec dev bash
```

## 5. Start project
```bash
# docker compose exec dev bash -c "cmake -S . -B build && cmake --build build && ./build/sfml-test"
docker compose exec dev bash -c "rm -rf build && cmake -S . -B build && cmake --build build && ./build/sfml-test"

```
replace ./build/sfml-test to the name of your executable (cf CMakeLists.txt last line add_executable)

```bash
docker compose exec dev bash -c "rm -rf build/*"
```