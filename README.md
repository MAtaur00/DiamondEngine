﻿# Diamond Engine

Diamond Engine is a 3D game engine created by Marc Tarrés and Aleix Castillo, two students of CITM, UPC in Terrassa. This code is written in C++.

- Marc Tarrés [Github account](https://github.com/MAtaur00)
- Aleix Castillo [Github account](https://github.com/AleixCas95)
- Diamond Engine [Github repository](https://github.com/MAtaur00/DiamondEngine)

## Features

- The engine accepts drag & drop for both 3D models and textures.
- As long as the textures are kept with their original name and as long as no files are corrupted, if the original textures for a 3D model are in the Textures folder in the engine, you can drag the original 3D model from anywhere in the computer and it will automatically load the textures and paint it.
- You can change the position, rotation and scale of the GameObjects from the Inspector window.
- You can Save and Load the scene from the File menu.
- All debugging options can be selected from Debug menu and also with the controls listed below.
- You can create shapes from the View menu, and check the configuration of the engine.
- Frustum culling can be activated in the camera to ignore out of view models.
- A "Play" button is available in the engine to switch to game mode (only if there's a camera component to use as the game camera). The camera used as the game camera will always be the last one created.

## Inputs & Shortcuts

#### Camera controls

- Alt + Right Click: Rotate camera
- Alt + WASD: Move the camera
- Alt + Left click: Orbit around the current Object
- F: Focus on the selected object
- Wheel: Zoom In and Out
- Shift: Double movement speed

### Engine controls

- F1 key: Paint AABBs of all Objects and Quadtree
- F2 key: Debug textures for all Objects
- F3 key: Activate/Deactivate culling for the game camera
- Mouse wheel click: Select Object. Objects can also be selected from inspector

## External Libraries

- ImGui
- ImGuizmo
- SDL
- OPENGL
- MathGeoLib
- PCG
- Assimp
- DevIL
- Parson

## Website

- Link to our website: https://mataur00.github.io/DiamondEngineMobirise/

## MIT License

Copyright (c) 2019 Marc Tarrés & Aleix Castillo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
