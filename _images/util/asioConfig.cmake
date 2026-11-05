find_path(ASIO_INCLUDE_DIR asio.hpp)

add_library(asio::asio INTERFACE IMPORTED)
set_target_properties(asio::asio PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${ASIO_INCLUDE_DIR}"
)

message(STATUS "asio::asio loaded!")