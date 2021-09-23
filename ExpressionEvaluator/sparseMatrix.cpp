#include <iostream>
#include <iomanip>
#include <ios>
#define DEF_TERM std::cout << "\033[0m\n"

class Sparse
{
public:
    Sparse(int r, int c, int d) : row(r), col(c), data(d), next(nullptr) {}

    int row, col, data;
    Sparse *next;
};

Sparse *insert(Sparse *mat, int r, int c, int d)
{
    Sparse *t = new Sparse(r, c, d);

    if (!mat)
    {
        mat = t;
        return mat;
    }
    Sparse *tmp = mat;
    while (tmp->next)
    {
        if (tmp->row == r && tmp->col == c)
            break;
        tmp = tmp->next;
    }

    if (tmp->row == r && tmp->col == c)
    {
        delete t;
        tmp->data += d;
        return mat;
    }

    tmp->next = t;
    return mat;
}

void deleteSparse(Sparse *m)
{
    if (!m)
        return;
    deleteSparse(m->next);
    delete m;
}

void display(Sparse *matrix)
{
    if (!matrix)
    {
        std::cout << "Empty\n";
        return;
    }
    Sparse *t = matrix;
    std::cout << "\033[33;38m";
    std::cout << "+" << std::setfill('-') << std::setw(22) << "+";
    DEF_TERM;
    do
    {
        std::cout << "\033[33;38m";
        // std::cout<<"| %4d | %4d | %5d |\n",t->row, t->col, t->data);
        std::cout << "| " << std::setfill(' ') << std::setw(4) << t->row
                  << " | " << std::setfill(' ') << std::setw(4) << t->col
                  << " | " << std::setfill(' ') << std::setw(5) << t->data << " |";
        DEF_TERM;
        t = t->next;
    } while (t);
    std::cout << "\033[33;38m";
    std::cout << "+" << std::setfill('-') << std::setw(22) << "+";
    DEF_TERM;
}

Sparse *addSparseMatrix(Sparse *m1, Sparse *m2)
{
    Sparse *res = 0;
    while (m1 && m2)
    {
        if (m1->row < m2->row)
        {
            res = insert(res, m1->row, m1->col, m1->data);
            m1 = m1->next;
        }
        else if (m1->row > m2->row)
        {
            res = insert(res, m2->row, m2->col, m2->data);
            m2 = m2->next;
        }
        else
        {
            if (m1->col < m2->col)
            {
                res = insert(res, m1->row, m1->col, m1->data);
                m1 = m1->next;
            }
            else if (m1->col > m2->col)
            {
                res = insert(res, m2->row, m2->col, m2->data);
                m2 = m2->next;
            }
            else
            {
                res = insert(res, m1->row, m1->col, (m1->data + m2->data));
                m1 = m1->next;
                m2 = m2->next;
            }
        }
    }

    while (m1)
    {
        res = insert(res, m1->row, m1->col, m1->data);
        m1 = m1->next;
    }

    while (m2)
    {
        res = insert(res, m2->row, m2->col, m2->data);
        m2 = m2->next;
    }

    return res;
}

int main(int argc, char const *argv[])
{
    Sparse *mat1 = 0;

    int ch;
    std::cout << "Enter the valid data for sparse matrix1\n";
    do
    {
        std::cout << "\033[33;37mEnter 1->insert data";
        DEF_TERM;
        std::cout << "\033[33;38mEnter 2->display";
        DEF_TERM;
        std::cout << "\033[33;35mEnter 0->EXIT";
        DEF_TERM;
        std::cout << "-> ";
        std::cin >> ch;
        switch (ch)
        {
        case 1:
            int r, c, d;
            std::cout << "Enter row col data: ";
            std::cin >> r >> c >> d;
            mat1 = insert(mat1, r, c, d);
            break;

        case 2:
            std::cout << "\t\tMatrix 1\n";
            display(mat1);
            break;
        }

    } while (ch);

    Sparse *mat2 = 0;
    std::cout << "Enter the valid data for sparse matrix2\n";
    do
    {
        std::cout << "\033[33;37mEnter 1->insert data";
        DEF_TERM;
        std::cout << "\033[33;38mEnter 2->display";
        DEF_TERM;
        std::cout << "\033[33;35mEnter 0->EXIT";
        DEF_TERM;
        std::cout << "-> ";
        std::cin >> ch;
        switch (ch)
        {
        case 1:
            int r, c, d;
            std::cout << "Enter row col data: ";
            std::cin >> r >> c >> d;
            mat2 = insert(mat2, r, c, d);
            break;

        case 2:
            std::cout << "\t\tMatrix 2\n";
            display(mat2);
            break;
        }

    } while (ch);

    Sparse *mat3 = addSparseMatrix(mat1, mat2);
    display(mat3);

    deleteSparse(mat1);
    deleteSparse(mat2);
    deleteSparse(mat3);

    return 0;
}
