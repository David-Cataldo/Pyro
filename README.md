# Pyro
Pyro Engine

(WINDOWS ONLY AT CURRENT TIME)
----Build Steps----
1.) Install git if not already installed
2.) Open command prompt from desired directory and enter command "git clone --recurse-submodules https://github.com/David-Cataldo/Pyro.git"
3.) Open the "GenerateProjects.bat" file in a text editor and change the version of visual studio to the one you plan on using
4.) Run the "GenerateProjects.bat" file 
5.) Open the generate .sln file and build "Sandbox"
6.) While building "Sandbox" all projects should successfully build except for "Pyro" which should fail*
7.) Then build "Pyro" and everything should work

* The "Pyro" project builds to a .dll which is placed in the bin folder with the "Sandbox.exe" file by a postbuild command. However, "Pyro" gets built before "Sandbox" so the first time we try to build it, there's no "Sandbox" bin folder for the .dll to be placed in, causing the build error. This is why we have to build "Pyro" again after sandbox.
