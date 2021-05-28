# mesh-viewer

OPenGL applications for viewing meshes

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake -G "Visual Studio 16 2019" ..
mesh-viewer/build $ start CS312-MeshViewer.sln
```

Your solution file should contain multiple projects, such as `mesh-viewer`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/mesh-viewer
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

# TODO: Screenshots and writeup

*Phong shading*
<img width="249" alt="phong1" src="https://user-images.githubusercontent.com/75322388/119921197-96dd6700-bf3b-11eb-88c3-3da501bf64e6.png">
<img width="245" alt="phong2" src="https://user-images.githubusercontent.com/75322388/119921199-9775fd80-bf3b-11eb-9c9f-62036127e610.png">

*Toon shading*
<img width="243" alt="toon1" src="https://user-images.githubusercontent.com/75322388/119921240-a65cb000-bf3b-11eb-95f2-e3debcf2505d.png">
<img width="205" alt="toon2" src="https://user-images.githubusercontent.com/75322388/119921242-a6f54680-bf3b-11eb-807e-03e7472f0d68.png">


