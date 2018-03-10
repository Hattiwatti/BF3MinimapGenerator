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

3. F1 to enable the UI and freecamera
    - Use WASD to move the camera
    - "Zoom" can be changed by changing the OrthoView size

4. With the UI open and the ortographical view enabled, drag an area for the minimap
    - Note that rendering is depending on camera height. Objects higher than the camera do not render
    - Resolution is the width and height of one cell in the grid in meters
    - The resulting images will be limited to window height

5. Press "Generate minimap"
    - Images will be dumped in Battlefield 3\BF3MinimapGenerator\LevelName\map#\grid_#_#.tga
    - A file called info.txt will also be created with the following data
        - Side length of one cell in pixels
        - Amount on cells in a row/column
        - Side length of one cell in world units
        - Center coordinate of each cell

### Binaries

[Latest binaries](http://files.1337upload.net/BF3MinimapGenerator-ebf8b9.zip)
