W05D1_Phys
* Adds a parameter to the shader to pass colour
* Intent was to introduce how to access uniform variables
* Colour is added to CGameObject. This value is passed to the shader
* The is a additional method on the factory to update the object colour, too. 

NOTE: In graphics, we'll be using a more involved (complicated) concept of "colour" called "material" so will abandon this one vec3 RGB colour item. 