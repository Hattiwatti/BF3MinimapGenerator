## Battlefield 3 Minimap Generator
A tool for generating minimaps for Battlefield 3 maps

### Dependencies & Credit
MinHook - https://github.com/TsudaKageyu/minhook

DirectXTex - https://github.com/Microsoft/DirectXTex

UI is done with ImGui - https://github.com/ocornut/imgui

FB SDK (with small changes and additions) - https://www.unknowncheats.me/forum/battlefield-3/90022-frostbite_sdk-eastl.html

### Usage

1. Start the game, join a server

2. Inject .dll into the game

3. Press INSERT to enable freecamera, DELETE for Orthographical view, F1 for UI

4. With the UI open and the ortographical view enabled, drag an area for the minimap
    - Note that rendering is depending on camera height. Objects higher than the camera do not render
    - Resolution is the width and height of one cell in the grid in meters
    - The resulting images will be limited to window height

5. Press "Generate minimap"
    - Images will be dumped in .tga format in the Battlefield 3 folder

### Binaries

[Latest binaries](http://files.1337upload.net/BF3MinimapGenerator-db8a7f.zip)
