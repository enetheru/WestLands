import bpy
import xml.etree.ElementTree as ET
from mathutils import Vector

def rts_makeHappen(context):
    scn = context.scene

    try:
        if( scn['rts_tiled_path'] == "" or scn['rts_tiled_blend'] == "" ):
            print("error")
            return
    except:
        print("exception error, select both tiled file and blend file")
        return
    
    tree = ET.parse( scn['rts_tiled_path'] )
    root = tree.getroot()
    width = int( root.get( 'height' ) )
    length = int( root.get( 'width' ) )
    layers = root.findall( 'layer' )
    tilemap = layers[0][0].text

    print(tilemap)

    try:
        # link all objects
        with bpy.data.libraries.load(scn['rts_tiled_blend'], link=True) as (data_from, data_to):
            data_to.objects = data_from.objects

        for ob in data_to.objects:
            scn.objects.link(ob)

    except:
        print("exception errro when attempting to link blend file")
        return

    obs = []
    ob = context.object
    rows = tilemap.splitlines()
    counter = 0
    for row in rows:
        columns = row.split(',')
        for column in columns:
            if( column == "" ):
                continue
            try:
                tile = bpy.data.objects["{}".format( int(column)-1 ) ]
            except:
                #print( "{} Not Found".format( column ) )
                counter += 1
                continue
            
            copy = tile.copy()
            copy.location = Vector(( counter % width, int(counter / length) * -1, 0))
            
            obs.append(copy)
                
            counter += 1

    for ob in obs:
        scn.objects.link(ob)
        ob.layers[1] = True
        ob.layers[0] = False

    print( "{} tiles processed".format( counter ) )

    scn.update()

class rts_opCreateTilemap(bpy.types.Operator):
    """Tooltip"""
    bl_idname = "object.rts_createtilemap"
    bl_label = "Simple Object Operator"

#    @classmethod
#    def poll(cls, context):
#        return context.active_object is not None

    def execute(self, context):
        rts_makeHappen(context)
        return {'FINISHED'}

class rts_CreateTilemap(bpy.types.Panel):
    bl_label = "Create Tilemap"
    #bl_idname = "SCENE_PT_layout"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'TOOLS'
    bl_context = "objectmode"
    bl_category = "SpringRTS"

    filepath = bpy.props.StringProperty(subtype="FILE_PATH")

    def draw(self, context):
        layout = self.layout

        scene = context.scene

        # Create a simple row.
        layout.label(text=" Select Tiled file:")
        layout.prop(scene, "rts_tiled_path")

        layout.label(text=" Select Blend file:")
        layout.prop(scene, "rts_tiled_blend")

        # Big render button
        layout.label(text="Generate Map")
        row = layout.row()
        row.scale_y = 3.0
        row.operator("object.rts_createtilemap")

def register():
    bpy.utils.register_class(rts_opCreateTilemap)
    bpy.utils.register_class(rts_CreateTilemap)
    bpy.types.Scene.rts_tiled_path = bpy.props.StringProperty \
      (
      name = "",
      default = "",
      description = "select the Tiled map (*.tmx) file",
      subtype = 'FILE_PATH'
      )

    bpy.types.Scene.rts_tiled_blend = bpy.props.StringProperty \
      (
      name = "",
      default = "",
      description = "select the Blender tiles to link",
      subtype = 'FILE_PATH'
      )


def unregister():
    bpy.utils.unregister_class(rts_opCreateTilemap)
    bpy.utils.unregister_class(rts_CreateTilemap)
    del cpy.types.Scene.rts_tiled_path
    del cpy.types.Scene.rts_blend_path


if __name__ == "__main__":
    register()
