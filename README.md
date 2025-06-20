# SKSE Plugin Template - PlayerSpeedBoost

## What this template does in-game

If compiled and loaded into the game correctly, the player will run 5x faster.

---

## Assumptions

- You're using **Windows 10 or 11**
- You know how to download from GitHub (Code → Download ZIP)
- You have **Skyrim LE / VR / SE / AE** installed and launched at least once
- You have **SKSE** installed: https://skse.silverlock.org/
- You use **Mod Organizer 2**  
  > (Adjusting for Vortex should be easy, but up to you. NOT recommended to NOT use a mod manager.)
- You're using an **administrator Windows account** (can install programs)

---

## 📁 Make your dev folders

> This is where you’ll install required packages.

- Go to `C:\` and create a folder called `sksedev`

This guide assumes that path. You can change it, but you’ll have to update the rest of the guide accordingly.

---

## ⚙️ Set Environment Variables

> This tells Visual Studio and CMake where things are. **These folders do not have to exist yet.**

1. Open Start Menu → type `Environment` → click **Edit the system environment variables**
2. Click `Environment Variables...`

Add the following **User Variables**:

### CMake
- Name: `CMAKE_ROOT`  
- Value: `C:\Cmake`  
  > _We will install CMake here later._

### Skyrim Folder
- Name: `SKYRIM_FOLDER`  
- Value: `C:\path-to-your-skyrim-install\Skyrim Special Edition`  
  > _Copy the full path from your Skyrim installation._

### (Optional) Skyrim Mods Folder
- Name: `SKYRIM_MODS_FOLDER`  
- Value: `D:\pathtoyourmodsfolder\mods`  
  > _Makes it easier to deploy the DLL into the mods folder for MO2/Vortex._  
  > ⚠️ Do **not** path this directly to an `SKSE` folder.

### VCPKG
- Name: `VCPKG_ROOT`  
- Value: `C:\sksedev\vcpkg`  
  > _We will install vcpkg here later._

---

## 📥 Required Downloads & Install Locations

### SKSE Template

- Create folder: `C:\sksedev\sksetemplate`
- Download: **[TODO: Add GitHub repo link here]**
- Extract contents of `SKSE_Template_Supertron-main` into `C:\sksedev\sksetemplate`

---

### Visual Studio 2022 Community

- Download: https://visualstudio.microsoft.com/downloads/
- Install to default location.
- During install, import `sksetemplate.vsconfig` from `C:\sksedev\SKSE_Template_Supertron`

> If already installed, rerun the installer and import `sksetemplate.vsconfig` again.

---

### CMake

> ❗ **DO NOT** use CMake v4.x.x — use **v3.31.8** only.

- Download: https://cmake.org/download/  
  _(File: `cmake-3.31.8-windows-x86_64.msi`)_
- Install to C:\Cmake, then use default settings. 

---

### VCPKG

- Create folder: `C:\sksedev\vcpkg`
- Download: https://github.com/microsoft/vcpkg
- Extract contents of `vcpkg-master` into `C:\sksedev\vcpkg`

---

## 🧠 Open the Template in Visual Studio

- Navigate to `C:\sksedev\`
- Right-click the `sksetemplate` folder → **Open with Visual Studio**

> On Windows 11: _Right-click → “Show more options” → “Open with Visual Studio”_

You should see many messages. When dependencies and setup are finished, you should see this message in the end:

```
1> CMake generation finished.
```

- If you encounter any build/config issues, click `Project` → `Delete Cache and Reconfigure`.  
  This ensures that the template's CMake project regenerates properly.


---

## 🛠 Compiling & Testing In-Game

- In Visual Studio (upper left) click → **Build** → **Rebuild All**

If successful, you'll see:
```
Rebuild All succeeded.
```

Then, activate the mod in MO2/Vortex and launch Skyrim. Your player should now run very fast.

---

## 🔧 Customization

> Want to rename and reuse this template for future projects? Here’s how:

### In `C:\sksedev\`

Edit `CMakeLists.txt`:
```cmake
project(PlayerSpeedBoost VERSION 0.0.1 LANGUAGES CXX)
```
Change to:
```cmake
project(YourPluginName VERSION 0.0.1 LANGUAGES CXX)
```
> No spaces.

Edit `vcpkg.json`:
```json
"name": "playerspeedboost",
```
Change to:
```json
"name": "yourpluginname",
```
> All lowercase, no spaces.

---

### In Visual Studio:

- Rename `PlayerSpeedBoost.cpp` → `YourPluginName.cpp`
- Rename `PlayerSpeedBoost.h` → `YourPluginName.h`

Then in the `.cpp` file with the new name:

```cpp
#include "YourPluginName.h"```
> Should be line 5.
```constexpr auto INI_PATH = "Data/SKSE/Plugins/YourPluginName.ini";```
> Should be line 17.

---

## 🎯 Conclusion

You can contact me on Nexus Mods — **username: Supertron**

I'm still learning SKSE plugin development but wanted to make setup easier for everyone else.  
If this guide has issues or breaks, let me know and I’ll update it.

**Happy modding!**
