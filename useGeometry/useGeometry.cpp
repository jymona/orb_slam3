#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace Eigen;

int main(int argc, char ** argv){
    Matrix3d rotation_matrix = Matrix3d::Identity();
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));
    cout.precision(3);
    cout << "Rotation matrix = \n" << rotation_vector.matrix() << endl;
    rotation_matrix = rotation_vector.toRotationMatrix();

    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation (by angle axis)" << v_rotated.transpose() << endl;
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation (by matrix)" << v_rotated.transpose() << endl;

    // euler_angle
    // ZYX: roll, pitch, yaw
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

    Isometry3d T = Isometry3d::Identity(); // In fact, it is a 4x4 matrix.
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1, 3, 4));
    cout << "Translation matrix = \n" << T.matrix() << endl;

    // R*v+t
    Vector3d v_transformed = T * v;
    cout << "v transformed = " << v_transformed.transpose() << endl;

    // Quaternion
    Quaterniond q = Quaterniond(rotation_vector);
    // (x, y, z, w)
    cout << "Quaternion from rotation vector = " << q.coeffs().transpose() << endl;
    q = Quaterniond(rotation_matrix);
    cout << "Quaternion from rotation matrix = " << q.coeffs().transpose() << endl;
    // qvq^{-1}
    v_rotated = q * v;
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;
    cout << "should be equal to" << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl;

    return 0;

}