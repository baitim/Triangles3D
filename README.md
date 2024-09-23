<h1 align="center">Triangles3D</h1>

## Description

 Implementation of the intersection of triangles in 3D.

## How to run

1. Clone <br>
    write <code>git clone https://github.com/baitim/Triangles3D.git</code> in terminal

2. Go to folder <br>
    write <code>cd Triangles3D</code> in terminal

3. Build <br>
    write <code>cmake . -B build ; cmake --build build</code> in terminal

4. Run <br>
    write <code>./build/src/triangles</code> in terminal <br>

## How to test

1. Prepare
    - Go to folder <br>
        write <code>cd tests/end_to_end</code> in terminal

    - Generate tests <br>
        write <code>python3 generate.py</code> in terminal

2. Testing
    - End to end & Unit<br>
        in root dir write <code>ctest --test-dir build</code> in terminal <br>
        maybe you will need these flags for the ctest <code>--rerun-failed --output-on-failure</code>

## Features
* Optimized by octree

<p align="center"><img src="https://github.com/baitim/Triangles3D/blob/main/images/cat.gif" width="40%"></p>

## Support
**This project is created by [baitim](https://t.me/bai_tim)**