/**
 * 3D Convex Hull Analysis
 * Generates random points in spheres and cubes, computes convex hulls,
 * and outputs results to CSV for statistical analysis.
 */

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Random.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

// CGAL type definitions
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef std::vector<Point_3> Points;

int main()
{
  // Create CSV output file
  ofstream outputFile("convex_hull_dataset.csv");
  if (!outputFile.is_open())
  {
    cerr << "Error: Could not create output file!" << endl;
    return 1;
  }

  // Write CSV header
  outputFile << "run_id,n_points,shape_type,convex_hull_vertices" << endl;

  // Configuration parameters
  int runs = 100; // Number of runs per configuration
  int run_id = 1; // Global run counter

  // Generate logarithmically spaced point counts from 10 to 100,000
  vector<int> arr;
  for (int i = 0; i < 20; i++)
  {
    int n = round(10 * pow(10000.0, i / 19.0));
    arr.push_back(n);
  }

  vector<string> shapes = {"sphere", "cube"};

  for (const string &shape_type : shapes)
  {
    cout << "\n=== Processing " << shape_type << " shape ===" << endl;

    for (auto n : arr)
    {
      cout << "Processing n = " << n << " points for " << shape_type << "..." << endl;

      // Seed the random number generator with current time to get different points each run
      CGAL::Random rng(static_cast<unsigned int>(time(nullptr) + run_id));

      for (int run = 1; run <= runs; run++)
      {
        Points points;

        // Generate random points based on shape type
        if (shape_type == "sphere")
        {
          CGAL::Random_points_in_sphere_3<Point_3> gen(1, rng);
          for (int i = 0; i < n; i++)
          {
            points.push_back(*gen++);
          }
        }
        else if (shape_type == "cube")
        {
          CGAL::Random_points_in_cube_3<Point_3> gen(1, rng);
          for (int i = 0; i < n; i++)
          {
            points.push_back(*gen++);
          }
        }

        // Compute 3D convex hull
        Polyhedron_3 hull_poly;
        CGAL::convex_hull_3(points.begin(), points.end(), hull_poly);

        cout << "  Run " << run << ": " << hull_poly.size_of_vertices() << " vertices" << endl;

        // Write results to CSV file
        outputFile << run_id << "," << n << "," << shape_type << ","
                   << hull_poly.size_of_vertices() << endl;

        run_id++;
        points.clear();
      }
    }
  }

  outputFile.close();

  return 0;
}
