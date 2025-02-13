<h1 align="center">Triangles3D</h1>

## Description

 Implementation of the intersection of triangles in 3D.

## How to integrate
 
 use [storage](https://github.com/baitim/ConanPackages), project = "triangles3d", version = "1.0", user = "baitim"

## How to run

1. Clone <br>
    <code>git clone https://github.com/baitim/Triangles3D.git</code>

2. Go to folder <br>
    <code>cd Triangles3D</code>

3. Prepare conan <br>
    <code>uv sync --group dev; source .venv/bin/activate</code><br>
    <code>conan profile detect --force</code>

4. Init dependencies <br>
    <code>conan install . --build=missing -s compiler.cppstd=gnu20</code><br>
    maybe you will need these flags for the conan <code>-s build_type=Debug</code>

5. Build <br>
    <code>cmake --preset release</code><br>
    <code>cmake --build build/Release</code>

6. Run <br>
    <code>./build/Release/src/triangles</code>

## How to test

* Testing
    - End to end & Unit<br>
        <code>ctest --test-dir build/Release --output-on-failure</code>

## Features
* Optimized by octree

<p align="center"><img src="https://github.com/baitim/Triangles3D/blob/main/images/cat.gif" width="40%"></p>

## Support
**This project is created by [baitim](https://t.me/bai_tim)**