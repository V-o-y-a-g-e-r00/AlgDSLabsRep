#Для копирования файлов

#set(rwxfileslist test.txt testscript.bash)

#Копируем исполнимые файлы
foreach(pattern_file IN LISTS rwxList)
    file(COPY ${SRCDIR}/${pattern_file} DESTINATION ${DSTDIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
endforeach(pattern_file)

#Копируем обычные (неисполнимые) файлы
foreach(pattern_file IN LISTS rwList)
    file(COPY ${SRCDIR}/${pattern_file} DESTINATION ${DSTDIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_WRITE GROUP_READ WORLD_READ WORLD_WRITE)
endforeach(pattern_file)

#file(COPY ${SRCDIR}/test.txt DESTINATION ${DSTDIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_WRITE GROUP_READ WORLD_READ)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testscript.bash DESTINATION ${CMAKE_CURRENT_BINARY_DIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

#foreach(pattern_file ${rwxfileslist})
#    add_custom_command(
#        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}"
#        COMMAND cmake -E copy
#        "${CMAKE_CURRENT_SOURCE_DIR}/${pattern_file}"
#        "${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}"
#        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${pattern_file}"
#    )
#endforeach(pattern_file )