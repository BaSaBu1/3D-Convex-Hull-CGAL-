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

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef std::vector<Point_3> Points;

int main()
{
  // Create output file in append mode to avoid overwriting
  ofstream outputFile("convex_hull_results.txt", ios::app);
  if (!outputFile.is_open())
  {
    cerr << "Error: Could not create output file!" << endl;
    return 1;
  }

  // Write headers to both console and file
  outputFile << "\n"
             << string(50, '=') << endl;
  outputFile << "3D Convex Hull Analysis Results for Sphere" << endl;
  outputFile << "===============================" << endl;
  time_t currentTime = time(nullptr);
  outputFile << "Generated on: " << ctime(&currentTime) << endl;

  int runs = 10;

  int arr[13] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};
  for (auto n : arr)
  {
    outputFile << "\n"
               << string(30, '-') << endl;
    outputFile << "Number of points (n) = " << n << endl;
    outputFile << "Number of runs = " << runs << endl;

    // Seed the random number generator with current time to get different points each run
    CGAL::Random rng(static_cast<unsigned int>(time(nullptr)));

    for (int run = 1; run <= runs; run++)
    {
      Points points;
      CGAL::Random_points_in_sphere_3<Point_3> gen(5, rng);

      for (int i = 0; i < n; i++)
      {
        points.push_back(*gen++);
        // Optionally write points to file (uncomment next line if you want all points)
        // outputFile << "Point " << i << ": (" << points[i].x() << ", " << points[i].y() << ", " << points[i].z() << ")" << endl;
      }

      // Create a polyhedron to hold the convex hull
      Polyhedron_3 hull_poly;
      CGAL::convex_hull_3(points.begin(), points.end(), hull_poly);

      // Output to both console and file
      cout << "Run " << run << ": " << hull_poly.size_of_vertices() << " vertices" << endl;
      outputFile << hull_poly.size_of_vertices() << endl;
      points.clear();
    }
  }

  // Close the file
  outputFile.close();
  cout << "\nResults appended to 'convex_hull_results.txt'" << endl;

  return 0;
}
