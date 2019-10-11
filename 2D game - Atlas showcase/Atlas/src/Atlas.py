import bpy 
import sys
#Change this dir to correct one if you want to use modules from different folder
sys.path.append('C:\\Program Files\\Python37\\Lib\\site-packages')
import importlib
from bpy.props import *
startAtlas = 0
PILINSTALLED = 0

bl_info = {
    "name": "Atlas creator",
    "author": "Andrzej Bosianek",
    "category": "Render"}
 

def installLib(package):
    try:
        try:
            from pip import main as pipmain
        except:
            from pip._internal import main as pipmain
        try:
            pipmain(['install', package])
            from PIL import Image
            PILINSTALLED = 1;
            print ("installation succesfull") 
        except:
            print ("installation failed")
    except ImportError:
        print ('pip not found. Installing.')
        try:
            import ensurepip
            ensurepip.bootstrap(upgrade=True, default_pip=True)
            import pip
            pip.main(['install'], package)
        except ImportError:
            print ('ensure pip and pip are not installed')


try:
    from PIL import Image
    PILINSTALLED = 1
    startAtlas = 0
except ImportError:
    print ('Image library is not installed')
    print ('Please install Pillow lib')
    PILINSTALLED = 0
    installLib('Pillow') 

def handle_finished_rendering(scene):
    global startAtlas
    global PILINSTALLED
	
	""" Check if PIL is installed and if we have started the atlas"""
	
    if(PILINSTALLED == 1 and startAtlas == 1):
        print("Render Completed!")
        scene = bpy.context.scene
        new_image = Image.new('RGBA', (max_rsx,max_rsy))
        outline_x = scene.outline
        outline_y = scene.outline
        rowsloop = 0
        columnsloop = 0
		
		""" Generate image and for each frame put image into correct row and column """
		
        for frame in range(int(scene.frame_start), int(scene.frame_end+1)):
            #outline_y = scene.outline
            while columnsloop < scene.columns:
                while rowsloop < scene.rows:
                    print(rowsloop,columnsloop)
                    #print(rowsloop*rsx+scene.outline, columnsloop*rsy+scene.outline)
                    image = Image.open(scene.render.frame_path(frame=frame))
                    new_image.paste(image, (rowsloop*rsx+outline_x, columnsloop*rsy+outline_y))
                    outline_x += scene.outline
                    print(frame)
                    frame += 1
                    rowsloop += 1
                    if(frame >= scene.frame_end+1):
                        new_image.save(scene.render.frame_path(frame=scene.frame_end+1))
                        startAtlas = 0
                        columnsloop = scene.columns
                        rowsloop = scene.rows
                        break
                columnsloop += 1
                outline_y += scene.outline
                rowsloop = 0
                outline_x = scene.outline
            outline_y = scene.outline
		""" Save finished image """	
        new_image.save(scene.render.frame_path(frame = scene.frame_end+1))
        print ("image saved to: " + scene.render.frame_path(frame= scene.frame_end+1))
        startAtlas = 0
    
class S_PT_SimPanel(bpy.types.Panel):
    bl_label = ""
    bl_space_type = "PROPERTIES"
    bl_region_type = "WINDOW"
    bl_context = "object"
    global rsx
    global rsy
    global max_rsx
    global max_rsy
    
    bpy.types.Scene.rows = bpy.props.IntProperty(
        name="Rows",
        description="Number of rows in atlas", 
        min = 1, max = 65536,
        default = 2)
    bpy.types.Scene.columns = bpy.props.IntProperty(
        name="Columns", 
        description="Number of columns in atlas",
        min = 1, max = 65536,
        default = 2)
    bpy.types.Scene.outline = bpy.props.IntProperty(
        name="Outline", 
        description="Outline thickness (pixels) on image",
        min = 0, max = 10000,
        default = 0)


    def draw_header(self, context):
        layout = self.layout
        layout.label(text="")
 
    def draw(self, context):
        layout = self.layout
        scn = context.scene
        obj = context.object
        
        
        row = layout.row()
        row.label(text="Active object is: " + obj.name)
        row = layout.row()
        row.prop(obj, "name")

        row = layout.row()
        row.label(text="no frames: " + str(scn.frame_end+1 - scn.frame_start ))
        row = layout.row()
        row.label(text="Start frame: " + str(scn.frame_start))
        row = layout.row()
        row.label(text="End frame: " + str(scn.frame_end+1))
        row = layout.row()
        row.operator("render.atlas")
        row = layout.row()
        row.prop(scn,'rows')
        row = layout.row()
        row.prop(scn, 'columns')
        row = layout.row()
        row.prop(scn, 'outline')

class AtlasOperator(bpy.types.Operator):
    bl_label = "Start Atlas"
    bl_idname = "render.atlas"
    bl_description = "Start Rendering and creating atlas"

    def execute(self, context):
        global startAtlas
        global PILINSTALLED
        global rsx
        global rsy
        global max_rsx
        global max_rsy
        if(PILINSTALLED == 0):
            self.report({'INFO'}, "library Pillow is not installed")
            print("library Pillow is not installed")
            return {'FINISHED'}
        else:
            if (bpy.context.scene.render.image_settings.file_format == "PNG" or
                bpy.context.scene.render.image_settings.file_format == "BMP" or
                bpy.context.scene.render.image_settings.file_format == "JPEG" or
                bpy.context.scene.render.image_settings.file_format == "JPEG 2000"):
                if(bpy.context.scene.rows * bpy.context.scene.columns >= 1):
                    startAtlas = 1
                    rsx = bpy.context.scene.render.resolution_x
                    rsy = bpy.context.scene.render.resolution_y
                    max_rsx = bpy.context.scene.render.resolution_x * bpy.context.scene.rows + (bpy.context.scene.outline*(bpy.context.scene.rows))+bpy.context.scene.outline
                    max_rsy = bpy.context.scene.render.resolution_y * bpy.context.scene.columns + (bpy.context.scene.outline*(bpy.context.scene.columns))+bpy.context.scene.outline
                    #bpy.context.window.screen = bpy.data.screens['3D View Full']
                    bpy.ops.render.render('INVOKE_DEFAULT',animation=True, use_viewport=True)
            else:
                self.report({'INFO', 'WARNING'}, "Wrong file format")
                print("Wrong file format")
            return {'FINISHED'}
 
classes = (
        AtlasOperator,
        S_PT_SimPanel,
)

""" Add handler when rendering is complete in Blender """
def register():
    from bpy.utils import register_class
    for cls in classes:
        register_class(cls)
    bpy.app.handlers.render_complete.append(handle_finished_rendering)       
   
""" Remove handler """
def unregister():
    from bpy.utils import unregister_class
    for cls in reversed(classes):
        unregister_class(cls)
    bpy.app.handlers.frame_change_pre.remove(handle_finished_rendering)   


if __name__ == "__main__":
    register()