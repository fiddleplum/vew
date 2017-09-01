# Javascript API

* vew
  * scene
    * addEntity() - returns the added entity
    * removeEntity(entity)
  * downloader
  * ? s3

* entity
  * getFrame() - frame
  * addComponent(type) - returns the added component
  * removeComponent(component)

* frame
  * getPosition() - [x, y, z]
  * setPosition([x, y, z])
  * getOrientation() - [w, x, y, z]
  * setOrientation([w, x, y, z])
  * getParent() - entity

* camera component
  * getFieldOfView() - number in degrees
  * setFieldOfView(fieldOfView)
  * getFieldOfViews() - [x, y] in degrees
  * getNearDistance() - number
  * setNearDistance(nearDistance)
  * getBounds() - [x, y, w, h] in 0 to 1 units
  * setBounds(bounds)
  * getPixelBounds() - [x, y, w, h] in pixels
  * transformFromCameraSpaceToPixelSpace([x, y, z]) - returns [x, y] in pixels
  * transformFromPixelSpaceToCameraSpace([x, y]) - returns [x, y, z] normalized

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
