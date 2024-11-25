// Exception.h
#include <exception>
#include <string>

class OpenGLException : public std::exception {
public:
    explicit OpenGLException(const std::string& message)
        : message_("OpenGL Error: " + message) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

void checkOpenGLError(const std::string& location, int line);

#define TO_STR(x) #x
#define GL(x) do { x; checkOpenGLError(#x, __LINE__); } while(0)

