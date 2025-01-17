# Computer Graphics – Meshes

## Background

### Read Section 12.1 of _Fundamentals of Computer Graphics (4th Edition)_.

### Skim read Chapter 11 of _Fundamentals of Computer Graphics (4th Edition)_.

There are many ways to store a triangle (or polygonal) mesh on the computer. The
data-structures have very different complexities in terms of code, memory, and
access performance. At the heart of these structures, is the problem of storing
the two types of information defining a mesh: the _geometry_ (where are points
on the surface located in space) and the _connectivity_ (which points are
connected to each other). The connectivity is also sometimes referred to as the
[topology](https://en.wikipedia.org/wiki/Topology) of the mesh.

The [graphics pipeline](https://en.wikipedia.org/wiki/Graphics_pipeline) works
on a per-triangle and per-vertex basis. So the simplest way to store geometry is
a 3D position <img src="/tex/ec6276257da0cb44caa5ae4b07afb40e.svg?invert_in_darkmode&sanitize=true" align=middle width=56.27160494999998pt height=26.76175259999998pt/> for each <img src="/tex/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/>-th vertex of the mesh. And to store
triangle connectivity as an ordered triplet of indices referencing vertices:
<img src="/tex/567132d8a883ab35cbb45db628ebb96e.svg?invert_in_darkmode&sanitize=true" align=middle width=36.147533399999986pt height=22.831056599999986pt/> defines a triangle with corners at vertices <img src="/tex/5474c8baa2bc6feabb0eac4237772aab.svg?invert_in_darkmode&sanitize=true" align=middle width=14.628015599999989pt height=14.611878600000017pt/>, <img src="/tex/4e86697c693f7bd2ebcf1bf515fbba2f.svg?invert_in_darkmode&sanitize=true" align=middle width=16.08162434999999pt height=14.611878600000017pt/> and <img src="/tex/fac5b28b95f69ccc2e9d37b26c68864f.svg?invert_in_darkmode&sanitize=true" align=middle width=17.24314514999999pt height=14.611878600000017pt/>.
Thus, the geometry is stored as a list of <img src="/tex/55a049b8f161ae7cfeb0197d75aff967.svg?invert_in_darkmode&sanitize=true" align=middle width=9.86687624999999pt height=14.15524440000002pt/> 3D vectors: efficiently, we can
put these vectors in the rows of a real-valued matrix <img src="/tex/907f9d3f474ec1dea25687fb39c395a7.svg?invert_in_darkmode&sanitize=true" align=middle width=73.77646979999999pt height=26.76175259999998pt/>. Likewise,
the connectivity is stored as a list of <img src="/tex/0e51a2dede42189d77627c4d742822c3.svg?invert_in_darkmode&sanitize=true" align=middle width=14.433101099999991pt height=14.15524440000002pt/> triplets: efficiently, we can put
these triplets in the rows of an integer-valued matrix <img src="/tex/c7299835acc0beb6d4c78f128f1d90cd.svg?invert_in_darkmode&sanitize=true" align=middle width=123.31228469999999pt height=26.76175259999998pt/>.

> **Question:** What if we want to store a (pure-)quad mesh?

### Texture Mapping

[Texture mapping](https://en.wikipedia.org/wiki/Texture_mapping) is a process
for mapping image information (e.g., colors) onto a surface (e.g., triangle
mesh). The standard way to define a texture mapping is to augment the 3D
geometric information of a mesh with additional 2D _parametrization_
information: where do we find each point on the texture image plane? Typically,
parameterization coordinates are bound to the unit square. 

Mapping a 3D flat polygon to 2D is rather straightforward. The problem of
finding a good mapping from a 3D surface to 2D becomes much harder if our
surface is not flat (e.g., like a
[hemisphere](https://en.wikipedia.org/wiki/Hemisphere)), if the surface does not
have exact one boundary (e.g., like a sphere) or if the surface has "holes"
(e.g., like a [torus/doughnut](https://en.wikipedia.org/wiki/Torus)).

Curved surfaces must get _distorted_ when flattened onto the plane. This is why
[Greenland looks bigger than
Africa](https://www.youtube.com/watch?v=vVX-PrBRtTY) on a common map of the
Earth.

The lack or presence of too many boundaries or the presence of "doughnut holes"
in surfaces implies that we need to "cut" the surface to lay out it on the
plane so all parts of the surface are "face up". _Think about trying to flatten
a deflated basketball on the ground._ 

### Normals

For a smooth surface, knowing the surface geometry (i.e., position in space)
near a point fully determines the [normal
vector](https://en.wikipedia.org/wiki/Normal_(geometry)) at that point.

For a discrete mesh, the normal is only well-defined in the middle of planar
faces (e.g., inside the triangles of a triangle mesh, but not along the edges or
at vertices). Furthermore, if we use these normals for rendering, the surface
will have a faceted appearance. This appearance is mathematically correct, but
not necessarily desired if we wish to display a smooth looking surface.

[Phong](https://en.wikipedia.org/wiki/Bui_Tuong_Phong) realized that [linearly
interpolating](https://en.wikipedia.org/wiki/Linear_interpolation) normals
stored at the corners of each triangle leads to a [smooth
appearance](https://en.wikipedia.org/wiki/Phong_shading#Phong_interpolation).

This raises the question: what normals should we put at vertices or corners of
our mesh? 

For a faceted surface (e.g., a cube), all corners of a planar face <img src="/tex/190083ef7a1625fbc75f243cffb9c96d.svg?invert_in_darkmode&sanitize=true" align=middle width=9.81741584999999pt height=22.831056599999986pt/> should
share the face's normal <img src="/tex/aa0f607fb8a0f302675de85aeabededc.svg?invert_in_darkmode&sanitize=true" align=middle width=59.845697999999985pt height=26.76175259999998pt/> .

For a smooth surface (e.g., a sphere), corners of triangles located at the same
vertex should share the same normal vector. This way the rendering is continuous
across the vertex. A common way to define per-vertex normals is to take a
weighted average of normals from incident faces. Different weighting schemes are
possible: uniform average (easy, but sensitive to irregular triangulations),
angle-weighted (geometrically well motivated, but not robust near zero-area
triangles), area-weighted (geometrically reasonable, well behaved). In this
assignment, we'll compute area-weighted per-vertex normals:

<p align="center"><img src="/tex/599fe3b222b5898bd240d6ac12d5c5b5.svg?invert_in_darkmode&sanitize=true" align=middle width=161.40208425pt height=41.4976122pt/></p>

where <img src="/tex/f947b3c602ca948910b99f1601e5abed.svg?invert_in_darkmode&sanitize=true" align=middle width=36.34324319999999pt height=24.65753399999998pt/> is the set of faces neighboring the <img src="/tex/6c4adbc36120d62b98deef2a20d5d303.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55786029999999pt height=14.15524440000002pt/>-th vertex.

[per-vertex-normal]: images/per-vertex-normal.png height=300px
![Unique triangle normals (orange) are well-defined. We can define a notion of a
normal for each vertex (purple) by taking a (weighted) average of normals from
incident triangles.][per-vertex-normal]

For surfaces with a mixture of smooth-looking parts and creases, it is useful to
define normals independently for each triangle corner (as opposed to each mesh
vertex). For each corner, we'll again compute an area-weighted average of normals 
triangles incident on the shared vertex at this corner, but we'll ignore
triangle's whose normal is too different from the corner's face's normal:

<p align="center"><img src="/tex/cc96dd182e07003c6232739259df10ec.svg?invert_in_darkmode&sanitize=true" align=middle width=245.6981736pt height=42.4291164pt/></p>

where <img src="/tex/1926c401973f24b4db4f35dca2eb381d.svg?invert_in_darkmode&sanitize=true" align=middle width=6.672392099999992pt height=14.15524440000002pt/> is the minimum dot product between two face normals before we declare
there is a crease between them.

![`./normals` should open a viewing window. Toggling `1`,`2`,`3` should switch
between normal types. Notice that per-face has sharp corners, but a faceted
appearance in the curved regions; the per-vertex has nice smooth regions but
ugly corners where averaging acts up; and per-corner is the best of both
worlds.](images/fandisk-normals.png)

### .obj File Format

The [.obj file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file) is a
_face_-based representation of a mesh. The connectivity/topological data is
stored implicitly by a list of a faces whose corners can _share_ geometric
information.

There are three main types of geometric information stored at vertices:

  - 3D position information (let's call it `V`),
  - 3D normal vector information (let's call it `NV`), and
  - 2D parameterization information (let's call it `UV`).

Faces know where to find the position, normal and parameterization information
for each corner by following a pointer/index. For a given corner of a given
face, the index for position, normal or parameterization information may be
different.

> **Warning:** In C++ indices ["start"]() at `0`, but in a .obj file the first
> element in a list has index `1`.

![Running `./obj` will first pop up a viewer with your generated cube textured
with a [Rubik's
cube](https://en.wikipedia.org/wiki/Rubik%27s_Cube)](images/rubiks-cube.gif)

![After closing that window, another viewer will pop up with your generated sphere textured
with the earth.](images/earth.gif)

##### Cube example

In this way, the quadrilateral faces of a cube mesh may use 8 unique
3D vertex positions, giving the appearance of a connected surface when visualized
in 3D. The same set of faces may use 14 unique 2D parameterization positions,
giving the appearance of a cross with a boundary when visualized in 2D. Finally,
that same set of faces may use only 6 unique 3D normal vectors.

![](images/cube.png)

### Eigen Matrices

Every row of `Eigen::MatrixXd` can store a mesh vertex position using _doubles.

Every row of `Eigen::MatrixXi` can store a list of indices into rows of position
matrix using integers as _indices_.

Use `.resize(num_rows,num_cols)` to resize a matrix to be `num_rows` by
`num_cols`. Use `X = Eigen::MatrixXd::Zero(num_rows,num_cols)` to resize and initialize a
matrix with zeros.

### Subdivision Surfaces

A [subdivision surface](https://en.wikipedia.org/wiki/Subdivision_surface) is a
natural generalization of a [spline
curve](https://en.wikipedia.org/wiki/Spline_(mathematics)). A smooth spline can
be defined as the [limit](https://en.wikipedia.org/wiki/Limit_(mathematics)) of
a [recursive
process](https://en.wikipedia.org/wiki/Recursion_(computer_science)) applied to
a polygon: each edge of the polygon is split with a new vertex and the vertices
are smoothed toward eachother. If you've drawn smooth curves using Adobe
Illustrator, PowerPoint or Inkscape, then you've used splines.

At a high-level, subdivision surfaces work the same way. We start with a
polyhedral mesh and subdivide each face. This adds new vertices on the faces
and/or edges of the mesh. Then we smooth vertices toward each other.

The first and still (most) popular subdivision scheme was invented by
[Catmull](https://en.wikipedia.org/wiki/Edwin_Catmull) (who went on to co-found
[Pixar](https://en.wikipedia.org/wiki/Pixar)) and
[Clark](https://en.wikipedia.org/wiki/James_H._Clark) (founder of
[Silicon Graphics](https://en.wikipedia.org/wiki/Silicon_Graphics) and
[Netscape](https://en.wikipedia.org/wiki/Netscape)). [Catmull-Clark
subdivision](https://en.wikipedia.org/wiki/Catmull–Clark_subdivision_surface) is
defined for inputs meshes with arbitrary polygonal faces (triangles, quads,
pentagons, etc.) but always produces a pure-quad mesh as output (i.e., all faces
have 4 sides).

To keep things simple, in this assignment we'll assume the input is also a
pure-quad mesh.

![Running `./quad_subdivision` and repeated pressing _space_ will show this
[Bob](http://www.cs.cmu.edu/~kmcrane/Projects/ModelRepository/#bob) converging
toward a smooth surface.](images/bob-subdivision.gif)

## Mesh Viewers

[Mesh Lab](http://www.meshlab.net) is a free mesh-viewer used widely in computer
graphics and computer vision research. **_Warning_:** Mesh Lab does not appear
to respect user-provided normals in .obj files.

[Autodesk Maya](https://en.wikipedia.org/wiki/Autodesk_Maya) is a commericial 3D
modeling and animation software. They often have [free student
versions](https://www.autodesk.com/education/free-software/maya).

## Tasks

### White list

You're encouraged to use `#include <Eigen/Geometry>` to compute the [cross
product](https://en.wikipedia.org/wiki/Cross_product) of two 3D vectors
`.cross`.

### Black list

This assignment uses [libigl](http://libigl.github.io) for mesh viewing. libigl
has many mesh processing functions implemented in C++, including some of the
functions assigned here. Do not copy or look at the following implementations:

`igl::per_vertex_normals`  
`igl::per_face_normals`  
`igl::per_corner_normals`  
`igl::double_area`  
`igl::vertex_triangle_adjacency`  
`igl::writeOBJ`  

### `src/write_obj.cpp`

Write a pure-triangle or pure-quad mesh with 3D vertex positions `V` and faces
`F`, 2D parametrization positions `UV` and faces `UF`, 3D normal vectors `NV`
and faces `NF` to a `.obj` file.

> **Note:** These _two_ function overloads represent only a small subset of
> meshes and mesh-data that can be written to a `.obj` file. 

### `src/cube.cpp`

Construct the quad mesh of a cube including parameterization and per-face
normals.

> **Hint:** Draw out on paper and _label_ with indices the 3D cube, the 2D
> parameterized cube, and the normals.

### `src/sphere.cpp`

Construct a quad mesh of a sphere with `num_faces_u` × `num_faces_v` faces.

### `src/triangle_area_normal.cpp`
Compute the normal vector of a 3D triangle given its corner locations. The
output vector should have length equal to the area of the triangle.

### `src/per_face_normals.cpp`
Compute per-face normals for a triangle mesh.

### `src/per_vertex_normals.cpp`
Compute per-vertex normals for a triangle mesh.

### `src/vertex_triangle_adjacency.cpp`
Compute a vertex-triangle adjacency list. For each vertex store a list of all
incident faces.

### `src/per_corner_normals.cpp`
Compute per corner normals for a triangle mesh by computing the area-weighted
average of normals at incident faces whose normals deviate less than the
provided threshold.

### `src/catmull_clark.cpp`

Conduct `num_iters` iterations of [Catmull-Clark
subdivision](https://en.wikipedia.org/wiki/Catmull–Clark_subdivision_surface) on
a **pure quad** mesh (`V`,`F`).

