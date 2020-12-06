
# 源码文件路径
file(GLOB srcs  *.c )
#                mqtt/*.c
#                ota/*.c
#                pppos/*.c
#                tcp/*.c


# 头文件路径
set(include_dirs .) 
#                mqtt
#                ota
#                pppos
#                tcp

                
idf_component_register(SRCS "main.c" "${srcs}"
                       INCLUDE_DIRS "${include_dirs}")
#                       CA证书
#                       EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem