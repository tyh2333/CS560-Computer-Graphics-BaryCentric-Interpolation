# CS560-Computer-Graphics-BaryCentric-Interpolation
1. Texture interpolation and geometric warping

Description:  Texture warping is a typical application of the graphical object manipulation. The basic operation is a triangle-based or quadrilateral-based transformation using either affine, or bilinear, or projective transformation.  This assignment is designed to deform an image in a 2D space with interaction by using mouse to click and drag in real time. The warping consists of geometric shape warping and texture warping. This assignment is to enhance the concept of geometric warping, texture (image) operation, and interpolation.

Your implementation:  In this assignment, you will implement the warping by deforming corner vertices of a rectangle. Meanwhile, the texture should be mapped onto the deformed rectangle area. 
![image](https://user-images.githubusercontent.com/29907622/114823657-d38d3e80-9d91-11eb-93e5-f4ef6422cac4.png)

Your implementation consists of:
(a)Load and display the image “flower.bmp”.
(b)Draw a rectangle (you can define the size by yourself)
(c)Map the loaded image onto the rectangle area.

Implement following two functions:
  
(1)Place the mouse cursor on the center of the rectangle (blue dot), click to select the center vertex as an anchor vertex, then drag the anchor vertex to a certain place until the mouse button is released (red dot). During the procedure of deforming the rectangle, apply the texture mapping simultaneously. (Or: you can do an alternative deformation: Place the mouse in the corner of the rectangle, and stretch the rectangle plus texture mapping).40points

(2)Automatically rotate the image 360 degrees around z axis (display the image every 30 degrees) （30points）

                              
(3)Load a 3D model from a file (.OBJ format) (e.g., teapot, car, or robot). File name can be hardcoded. Use mouse to rotate and/or zoom the teapot model.（20points）
![image](https://user-images.githubusercontent.com/29907622/114823713-e30c8780-9d91-11eb-940f-ae456877602e.png)
![image](https://user-images.githubusercontent.com/29907622/114823722-e6a00e80-9d91-11eb-9fdc-e03903f71e16.png)
![image](https://user-images.githubusercontent.com/29907622/114823733-e99aff00-9d91-11eb-9a9b-faaaf8f393fe.png)
   
(4) Extra points:  Deform the model surface by a mouse; Map a texture to an arbitrary patch of the teapot surface.


(5)Extra points: Draw a CUBE, map the texture on the CUBE (6 faces). The CUBE can be viewed from any angles controlled by mouse. The CUBE can be resized or deformed by moving its corner by the mouse.  
Note: The texture mapping is implemented using the inverse mapping approach (do not use OpenGL texture mapping function)  
