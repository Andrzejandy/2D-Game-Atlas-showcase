### About Blender 2D Atlas Generator.
This project contains two programs:
- Atlas - Blender plugin written in Pyhton used to generate image atlas from animations in Blender.
- 2D_Game_Atlas - 2D animation showcase usage of Atlas plugin generated images. This program uses two atlas generated images for walking and standing: Walk.png, Stand.png which are located in Data/Textures/Player

Controls:
2D_Game_Atlas: Please open 2D_Game_Atlas.exe to run the program.

WASD - move character.
ESC - exit program.
Mouse scroll wheel - change scale.


Atlas: 
This project contains python Atlas.py plugin and blender file atlas.blend with already set up example which shows the 2d walking animation. 
Walking animation has been taken from: https://github.com/SebLague/Blender-to-Unity-Character-Creation/tree/master/Blend%20files

In order to generate the atlas image:
1. Open the atlas.blend file.
2. Click on the button "Run Script" on the bottom of the text editor.
3. On the right "Atlas generator" tab will appear which allows you to change the number of rows, columns and outline for the atlas generator.
4. Once you click the "Start atlas", rendering will start and once it finished the atlas image will appear in Output directory which is by default: C:/tmp\

### Example
Example of generated atlas for staying and walking animation from 3D Blender model. 
![Staying](https://raw.githubusercontent.com/Andrzejandy/2D-Game-Atlas-showcase/master/2D%20game%20-%20Atlas%20showcase/My2DGame/Data/Textures/Player/Stay.png)
![Walking](https://raw.githubusercontent.com/Andrzejandy/2D-Game-Atlas-showcase/master/2D%20game%20-%20Atlas%20showcase/My2DGame/Data/Textures/Player/Walk.png) 
