#include "../include/Triangle.hpp"

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Triangle::Triangle()
{
    this->p1 = Point();
    this->p2 = Point();
    this->p3 = Point();
}

Point Triangle::getp1()
{
    return this->p1;
}

Point Triangle::getp2()
{
    return this->p2;
}
Point Triangle::getp3()
{
    return this->p3;
}

void Triangle::serialize(std::ofstream *triangulos)
{
    this->p1.serialize(triangulos);
    *triangulos << " | ";
    this->p2.serialize(triangulos);
    *triangulos << " | ";
    this->p3.serialize(triangulos);
    *triangulos << "\n";
}