#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

void print_mat4(glm::mat4 mat)
{
    for (int col = 0; col < 4; col++)
    {
        std::cout << std::fixed // fix the number of decimal digits
                  << std::setprecision(2);

        // GLM stores matrices isong a column major order.
        std::cout << std::setw(6) << mat[0][col] << " " << std::setw(6) << mat[1][col] << " "
                  << std::setw(6) << mat[2][col] << " " << std::setw(6) << mat[3][col] << std::endl;
    }
}

int main()
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(3.0f, 3.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

    std::cout << glm::to_string(trans) << std::endl;

    print_mat4(trans);
}