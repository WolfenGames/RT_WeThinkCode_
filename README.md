# RT_WeThinkCode_

## What is this?
This is a rendering project creating by us few students from we think code, Ibotha, Jwolf and Jdorner. It implements the raytracing technique to display photorealistic...ish images. We have implemenented Refraction, Reflection, Multithreading, Shadows, Textures and Soon enough polygons.

![Heller?](https://github.com/WolfenGames/RT_WeThinkCode_/blob/master/Screen%20Shots/Celestial%20crystal%20ball.jpg)
![Other?](https://github.com/WolfenGames/RT_WeThinkCode_/blob/master/Screen%20Shots/Moon%20Church.jpg)


## Usage

Make sure you have mlx insalled on your mac...I know I am sorry, we only support mac...then run make and after the executable is made run the program as follows:

./RT SCENE.xml

where SCENE is your desired scene to render

## Making a Scene

The scenes are parsed using an xml-like format. In general every scene needs at least a camera. There are a few example scenes under scenes

[Example Scene](https://github.com/WolfenGames/RT_WeThinkCode_/blob/master/scenes/light.xml)

An importat part about making a scene is that every objects name must be unique. if you create 2 objects named "BOB" You will have one object with shared properties, as if all properties were writen within one scope.

Within a scene there are four parts, all of these types are declared as such 

\<type name="name"\>

  body
  
 \</type\>
 
 
 the only exeption to this declaration is the scene which does not have a name

### scene

These are scene wide variables such as:

A RayDepth (How many times the rays bounce)    \<raydepth\> D \</raydepth\>


### camera
 
The camera has 4 sub-parts, all of witch are declared in the body:

An origin                                      \<origin> x, y, z \</origin>

A rotation                                     \<rotation> x, y, z \</rotation>

An aperture                                    \<apurture> A \</aperture\>

A Field of View                                 \<FOV> FOV \</FOV>


### light
 
The light has 5 sub-parts, all of witch are declared in the body:

An origin (in case of point light              \<origin\> x, y, z \</origin\>

A direction (in case of directional light)     \<direction\> x, y, z \</direction\>

A colour                                       \<colour\> r, g, b \</colour\>

An intensity                                   \<intensity\> I \</intensity\>

A type                                         \<tpye\> point/directional \</type\>


### object
 
The light has 10 sub-parts, all of witch are declared in the body:

An origin (in case of point light              \<origin\> x, y, z \</origin\>

A rotation                                     \<rotation\> x, y, z \</rotation\>

A scale                                        \<scale\> x, y \</scale\>

A surfacecolour                                \<surfacecolour\> r, g, b \</surfacecolour\>

A specularcolour                               \<specularcolour\> r, g, b \</specularcolour\>

A texture                                      \<texture\> Tex.xpm \</texture\>

A texturescale                                 \<texturescale\> x, y \</texturescale\>

A transparency                                 \<transparency\> T \</transparency\>

A refractionindex                              \<refractionindex\> R \</refractionindex\>

A type                                         \<tpye\> sphere/plane/cylinder/cone \</type\>

