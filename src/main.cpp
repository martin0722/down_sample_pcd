#include <iostream>
#include <experimental/filesystem>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

namespace fs = std::experimental::filesystem;

int main (int argc, char** argv)
{
    for (auto & inputFile : fs::directory_iterator(argv[1]))
    {
        PCL_WARN("processing %s\n",
            fs::path(inputFile).filename().string().c_str());

        pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2());
        pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2());

        pcl::PCDReader reader;
        if (reader.read (fs::path(inputFile).string(), *cloud) == -1)
        {
            PCL_ERROR("Couldn't read file %s\n",
                fs::path(inputFile).filename().string().c_str());
        }
        else
        {
            // if (cloud->width * cloud->height > 200000)
            // {
                PCL_WARN("PointCloud before filtering: %d data points (%s)\n",
                    cloud->width * cloud->height,
                    pcl::getFieldsList(*cloud).c_str());

                pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
                sor.setInputCloud (cloud);
                sor.setLeafSize(0.2f, 0.2f, 0.2f);
                sor.filter (*cloud_filtered);

               PCL_WARN("PointCloud after filtering: %d data points (%s)\n\n",
                   cloud_filtered->width * cloud_filtered->height,
                   pcl::getFieldsList(*cloud_filtered).c_str());
                pcl::PCDWriter writer;
                writer.writeBinaryCompressed(
                    "out/" + fs::path(inputFile).filename().string(),
                    *cloud_filtered);
            // }
        }
    }

  return 0;
}
