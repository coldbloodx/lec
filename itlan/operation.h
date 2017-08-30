class Operation
{
    public:
        template <typename T>
            T add(T lhs, T rhs);
        template <typename T>
            T sub(T lhs, T rhs);
        template <typename T>
            T mul(T lhs, T rhs);
        template <typename T>
            T div(T lhs, T rhs);
};

template <typename T>
T Operation::add(T lhs, T rhs)
{
    return (T)(lhs + rhs);
}

template <typename T>
T Operation::sub(T lhs, T rhs)
{
    return (T)(lhs - rhs);
}


template <typename T>
T Operation::mul(T lhs, T rhs)
{
    return (T)(lhs * rhs);
}

template <typename T>
T Operation::div(T lhs, T rhs)
{
    return (T)(lhs / rhs);
}
