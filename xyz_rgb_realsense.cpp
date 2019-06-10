#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include "example.hpp"          // Include short list of convenience functions for rendering
#include <fstream>            

using namespace std;

std::tuple<uint8_t, uint8_t, uint8_t> get_texcolor(rs2::video_frame texture, rs2::texture_coordinate texcoords)
{
	const int w = texture.get_width(), h = texture.get_height();
	int x = std::min(std::max(int(texcoords.u*w + .5f), 0), w - 1);
	int y = std::min(std::max(int(texcoords.v*h + .5f), 0), h - 1);
	int idx = x * texture.get_bytes_per_pixel() + y * texture.get_stride_in_bytes();
	const auto texture_data = reinterpret_cast<const uint8_t*>(texture.get_data());
	return std::tuple<uint8_t, uint8_t, uint8_t>( texture_data[idx], texture_data[idx + 1], texture_data[idx + 2] );
}

int main(int argc, char * argv[])
{
	rs2::pointcloud pc;
	rs2::points points;
	rs2::pipeline pipe;
  
	cout << "Fetching frame from Camera ... \n";
	pipe.start();
	auto frames = pipe.wait_for_frames();

	auto color = frames.get_color_frame();
	if (!color)  color = frames.get_infrared_frame();

	pc.map_to(color);
	auto depth = frames.get_depth_frame();
	points = pc.calculate(depth);

	auto vertices = points.get_vertices();
	auto tex_coords = points.get_texture_coordinates();	

	int h = depth.get_height();
	int w = depth.get_width();
	int r, g, b;
	
	std::ofstream myfile;
	std::stringstream filename;

	filename << "Frame_Data"<< ".txt";
	myfile.open(filename.str());
	cout << "Going to write on a file ... \n";

	for (int i = 0; i < points.size(); i++)
	{
		if (vertices[i].z)
		{
			myfile << vertices[i].x << " " << vertices[i].y << " "<< vertices[i].z;
			std::tuple<uint8_t, uint8_t, uint8_t> current_color;
			current_color = get_texcolor(color, tex_coords[i]);
			r = std::get<0>(current_color);
			g = std::get<1>(current_color);
			b = std::get<2>(current_color);
			myfile << " "<<r << " " << g << " " << b << "\n";
		}
	}
	myfile.close();
  
system("pause");
return EXIT_SUCCESS;
}
