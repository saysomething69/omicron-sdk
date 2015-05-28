# omegalib 2.0 #

## Library Refactoring ##
### Revise Equalizer display system ###
  * There is probably a lot of redundancy in the initialization flow - inefficiency in the current way the Equalizer / application init flow works. Revise it.
  * **?** Render interlaced & side by side directly inside channel render function without relying on equalizer config and multiple equalizer draw calls
    * Would allow to work around some problems with equalizer
    * Would this lead to better performance?
  * create autogenerator of eq configurations using libconfig

### Revise Event class ###
  * Zoom -> Scale
  * split: convert to Scale
  * Remove SplitStart / SplitEnd, RotateStart, RotateEnd
  * Remove DoubleClick
  * Remove MoveUp, Down, Etc. events?

## Refactor Event class, generic messaging support ##

## Multimachine / distributed app changes ##

## SAGE Integration ##
Send pixels to SAGE through SAIL. Options:
  * Integrate as separate display system (I would have to take care of doing off-axis projection and a bunch of other stuff) **NO**
  * Integrate on top of display system at:
    * omega/DisplaySystem level (more generic)
    * oengine level (allows me to use Camera / RenderPass functionality)

Create `IFrameListener` interface.
Called by display system whenever a frame has finished rendering (per-client.) Gives back to the implementer enough info (i.e. a RenderTarget?) to
capture the framebuffer contents and do whatever with them.

DisplaySystem supports attaching a `IFrameListener`, but the same can be done on a camera **MOST FLEXIBLE SOLUTION**

Implement a `SailService` service class, deriving from `IFrameListener` as well. `SailService` can connect to SAGE through Sail, receive SAGE messages
and (if the application is a graphical application) register itself to the display system (or to a camera) to send pixel output to SAGE.

Starting / Stopping the service connects/disconnects to SAGE, so the application has control over the streaming.

Multiple sail service instances can create multiple windows on SAGE from the same omegalib application (i.e a Vtk app displaying multiple plots on a SAGE display)

Sail UI capabilities can be used to create a view + control panel on a SAGE display

## NGCave / eqc autoconfig tool ##
  * `HorzontalTiles, VerticalTiles` tile count
  * `ReferenceTile(RT)[ix, iy]` index of tile whose center is reference point R
  * NOTE: ReferenceTile normal is always +Z in global reference frame
  * `ReferenceOffset(RO)` offser of R wrt origin of system
  * `TileSize(TS)[w, h]` tile width, height

NOTE, RT corners easy to find.
> (i.e. `RTtl = RO - <-TSw/2, -TSh/2, 0>`)

  * `ConfigurationType` [Planar, Cylindrical]
  * `ColumnYawIncrement` angle variation on Y axis between one tile column and next.	Columns left of RT column have positive increment, right have negative.

Output text file:
> `TileIndex[ix, iy] TileCorners[tl, tr, bl, br]`



## Memory management and statistics support ##
Add a way to collect info about memory leaks, allocations and timing statistics in the application.
  * Allow those statistics to be viewed as an OSD (like the console)

## Other stuff ##
  * make osg & vtk data a downloadable package.
  * re-add vtk support