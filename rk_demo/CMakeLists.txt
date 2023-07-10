cmake_minimum_required(VERSION 3.8)

project(rk_demo)

include_directories(
	${PROJECT_SOURCE_DIR}/
	${PROJECT_SOURCE_DIR}/home
	${PROJECT_SOURCE_DIR}/furniture_control
	)

if (LV_DRV_USE_SDL_GPU)
	add_definitions(-DUSE_SDL_GPU=1)
endif()
if (LV_DRV_USE_DRM)
	add_definitions(-DUSE_DRM=1)
endif()

aux_source_directory(. SRCS)
aux_source_directory(./home SRCS)
aux_source_directory(./furniture_control SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
	lvgl pthread m lv_drivers freetype
)

if (LV_DRV_USE_SDL_GPU)
	target_link_libraries(${PROJECT_NAME} SDL2)
endif()
if (LV_DRV_USE_DRM)
	target_link_libraries(${PROJECT_NAME} drm)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

