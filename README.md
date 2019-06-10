# How to get XYX and RGB data from Intel Realsense D400

This tutorial shows simple method for fetching real-world cordinates using intel RealSense SDK 2.0.

### Prerequisites

We are not pcl library, But the one shipped with intel RealSense SDK 2.0

```
intel RealSense SDK 2.0
RealSense Camera D400
```

### Explaination
Simply fetched two steams without any extra configurations, used methods from [PointCloud](https://github.com/IntelRealSense/librealsense/tree/master/examples/pointcloud) example
```
auto color = frames.get_color_frame();
auto depth = frames.get_depth_frame();
points = pc.calculate(depth);
auto vertices = points.get_vertices();
auto tex_coords = points.get_texture_coordinates();
```
get_texcolor() is a method that can conver u,v values to RGB values and return tuple
```
current_color = get_texcolor(color, tex_coords[i]);
```
Simply saving these values in .txt file as X Y Z R G B format e.g.
```
-0.315017 -0.290297 0.7524 61 60 60
-0.313815 -0.290297 0.7524 61 60 60
-0.312404 -0.290104 0.7519 61 60 62
-0.311203 -0.290104 0.7519 61 60 62
-0.309753 -0.289873 0.7513 61 60 62
```

### Acknowledgments

* [Yonatan-Sade](https://github.com/Yonatan-Sade)
