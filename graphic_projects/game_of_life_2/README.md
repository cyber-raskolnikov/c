I was in your shoes just last year, and I'm no expert, but I think I can help get you started.

First of all, I would recommend you build Raylib from the source rather than installing through Homebrew. This way you can decide which version of Raylib to use on a per-project basis.

To get the source, you want to visit the latest release on the Github repo (https://github.com/raysan5/raylib/releases/tag/4.0.0) and under 'Assets' download 'Source code (zip)', NOT the precompiled one with 'macos' in the name.

Once downloaded, unzip 'raylib-4.0.0'.

From inside this folder you should see another called 'src'. Right-click the folder and at the bottom of the File Panel choose 'New Terminal at Folder'. This will open a Terminal window with the current working directory set to 'src'.

From here, just type 'make' (no quotes) and hit return. Raylib will begin compiling.

If all went well you should now have a file called 'librarylib.a' in the src folder.

In a separate window, navigate to where you want to keep your Raylib projects.

Now we're going to make a template for ourselves, not download one!

In your projects folder, make a folder called 'Template' and if you want, add the version of Raylib it uses to the name (in this case 'Template-4.0.0').

In your template, create a folder called 'lib'. This will store our project's libraries. From the 'src' folder, drag 'librarylib.a', 'raylib.h', and 'raymath.h' to 'lib'.

We no longer need the source folder 'raylib-4.0.0'.

I use VSCode for programming, so I'll explain how to setup a project in VSCode.

First, open VSCode and go to File->Open... and find your template folder. Click on it and hit 'Open'. If you're in the right folder, you should see the 'lib' folder listed in the VSCode file explorer.

Create new folder in the template folder and call it 'src'. This is where your project source files will go.

Still in 'Template-4.0.0', create another folder and call this one 'assets'. This is where all your project assets (textures, audio, shaders etc.) will go.

Create one more folder and call it 'bin'. This is the directory where our built .app will go.

Let's begin with some actual C code with Raylib.

In 'src', create a new file and name it main.c. You can name it whatever you want, but this way it's clear this is the root program.

First, let's include our libraries. At the top of the file:

#include "raylib.h"
#include "raymath.h"
If VSCode complains that either can't be found, quit VSCode and reopen the project. As long as you can 'CMD+Click' on them and open them in 'lib' you should be fine.

Under the includes, in a main function (this does have to be called main) paste this template code for now. This should get a window up and running when we are finished.

int main(void) { 
    InitWindow(400, 224, "Template-4.0.0");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
    
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}
We're going to create a makefile now that will build our project for us (I'm assuming you want to use C).

In Code, make a new file. The syntax here is the same as when working in the Terminal.

First things first, let's define our build command. Everything here should be typed as-is. No semi-colons or anything. Type:

build_osx:
We will call this command through VSCode's debugger.

Let's make some variables in this makefile to organize our arguments. Put these before the build command.

COMPILER = clang
Here we are specifying our C compiler. We're working on Macs so we use Clang. We will reference this variable in a final build command as $(COMPILER). I should note that this is an automation of typing 'clang --arguments' into the terminal directly.

SOURCE_LIBS = -Ilib/
This tells the compiler to add our 'lib' folder to the #include path so it can find Raylib.

OSX_OPT = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
This is macOS specific for building apps.

OSX_OUT = -o "bin/build_osx"
This tells the compiler where to put the .app.

CFILES = src/*.c
Tells the compiler where your project source files are i.e. 'main.c'. It will look for anything in the 'src' folder that ends in '.c'.

Now we can finally fill out our build command:

build_osx: 
    $(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT)
Save the file as 'makefile.mak'. Be sure to remove the .mak extension once saved or the make command will fail.

With 'main.c' open, hit 'F5' to start debugging. VSCode is currently not configured, so it will show a prompt. Choose the first option (C++ GBD/LLDB), then at the next prompt choose 'Clang' (This isn't that important because we will change this next)

VSCode will error, saying a launch program in the directory of main.c doesn't exist! Choose either option. What matters is that VSCode generated debugging templates. Under a new folder called .vscode (hidden in Finder), you should find 'launch.json', 'settings.json', and 'tasks.json'

In tasks.json, change the "type" from "cppbuild" to "shell". This specifies that we are running a Terminal program. Next set the "label" to "Build OSX". This is just for display when we hit 'F5' to Start Debugging. Set the "command" to "make build_osx". This tells VSCode to run our makefile. Lastly set "options" to {"cwd": "${workspaceFolder}"}. This lets VSCode know where we are working from.

You can remove the rest of the generated parameters ("args", "problemMatcher" etc.). Save and close tasks.json.

In launch.json, Change:

"program" from "${fileDirname}/${fileBasenameNoExtension}" to "${workspaceFolder}/bin/build_osx"

"cwd" from "${fileDirname}" to "${workspaceFolder}"

"preLaunchTask" from "C/C++: clang build active file" to "Build OSX"

Save and close launch.json.

And now, the moment you've been waiting for... Hit 'F5' once more and after a second or two you should have a blank window on your screen! You can now duplicate this template and begin your Raylib journey.

I hope this has helped, I know it's quite long but I tried to be very thorough. Please let me know how it goes!