from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add motor src files.
if GetDepend('PKG_USING_MOTOR'):
    src += Glob('src/motor.c')

# add motor include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('motor', src, depend = ['PKG_USING_MOTOR'], CPPPATH = path)
Return('group')