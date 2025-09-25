#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Random.h>
#include <vector>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef std::vector<Point_3> Points;

int main()
{
  int n = 100;
  Points points;

  CGAL::Random rng;
  CGAL::Random_points_in_cube_3<Point_3> gen(0.5, rng);

  for (int i = 0; i < n; i++)
  {
    points.push_back(*gen++);
    // printf("Point %d: (%f, %f, %f)\n", i, points[i].x(), points[i].y(), points[i].z());
  }

  // Create a polyhedron to hold the convex hull
  Polyhedron_3 hull_poly;
  CGAL::convex_hull_3(points.begin(), points.end(), hull_poly);

  std::cout << "Convex hull has " << hull_poly.size_of_vertices() << " vertices\n";
}
