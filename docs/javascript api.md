# Javascript API

* vew
  * addEntity() - the added entity
  * removeEntity(entity)
  * addViewport() - the added viewport
  * removeViewport(viewport)

* entity
  * getFrame() - frame
  * addComponent(type) - the added component
  * removeComponent(component)

* frame
  * getPosition() - [x, y, z]
  * setPosition([x, y, z])
  * getOrientation() - [w, x, y, z]
  * setOrientation([w, x, y, z])
  * getParent() - entity

* viewport
  * getCamera() - used camera
  * setCamera(camera)
  * getBounds() - [x, y, w, h] in 0 to 1 units
  * setBounds(bounds)
  * getPixelBounds() - [x, y, w, h] in pixels
  * transformFromCameraSpaceToPixelSpace([x, y, z]) - returns [x, y] in pixels
  * transformFromPixelSpaceToCameraSpace([x, y]) - returns [x, y, z] normalized

* camera component
  * getFieldOfView() - number in degrees
  * setFieldOfView(fieldOfView)
  * getFieldOfViews() - [x, y] in degrees
  * getNearDistance() - number
  * setNearDistance(nearDistance)

* model component
  * getMesh() - mesh
  * setMesh()
  * loadMesh(url)
  * ? loadMesh(s3)
  * ? saveMesh(s3)

* mesh
  * getVertices() - array of numbers
  * setVertices(vertices)
  * getIndices() - array of numbers
  * setIndices(indices)
