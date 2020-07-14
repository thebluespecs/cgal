#include <iostream>

#include <CGAL/Embree/AABB_tree.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL::Simple_cartesian<float> K;
typedef K::Point_3 Point;
typedef K::Triangle_3 Triangle;
typedef K::Ray_3 Ray;
typedef K::Vector_3 Vector;
typedef CGAL::Polyhedron_3<K> Polyhedron;

typedef CGAL::Embree::Triangle_mesh_geometry<Polyhedron, K, true> TriangleMesh;
typedef CGAL::Embree::AABB_tree<TriangleMesh, K> Tree;

int main(int argc, char *argv[])
{
    Point p(1.0, 0.0, 0.0);
    Point q(0.0, 1.0, 0.0);
    Point r(0.0, 0.0, 1.0);
    Point s(0.0, 0.0, 0.0);
    Polyhedron polyhedron;
    polyhedron.make_tetrahedron(p, q, r, s);

    Tree tree;
    tree.insert(polyhedron);

    // Configure the ray.
    Point rayOrigin(0.1f, 0.1f, -1.0f);
    Vector rayDirection(0.0f, 0.0f, 1.0f); /*Direction need not be normalized.*/
    Ray ray(rayOrigin, rayDirection);

    boost::optional<Tree::Intersection_and_primitive_id> intersection = tree.first_intersection(ray);

    // Below snippet explains how to recover the point from the Intersection_and_primitive_id return value.
    if(intersection){
        Point p = intersection->first;
        std::cout<<"Point of intersection : "<<p<<std::endl;
        // TriangleMesh::Primitive_id triangleInfo = intersection->second;
        // std::cout<<"Intersected triangle co-ordinates."<<std::endl;
        // Polyhedron::face_index fd = triangleInfo.first;
        // Polyhedron* polyhedron = triangleInfo.second;
        // Polyhedron::Halfedge_index hf = surfaceMesh->halfedge(fd);
        // for(Polyhedron::Halfedge_index hi : halfedges_around_face(hf, *surfaceMesh)){
        //     Mesh::Vertex_index vi = target(hi, *surfaceMesh);
        //     Point data = surfaceMesh->point(vi);
        //     std::cout<<data<<"/// ";
        // }
        std::cout<<std::endl;
    }
    return 0;
}
