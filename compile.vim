" NOTE - must have the dlls in the same folder 

" Compile SFML Project WITHOUT Audio
term clang++ -std=c++17 -Lc:\SFML\lib -IC:\SFML\include -lsfml-graphics -lsfml-window -lsfml-system  % -o %.exe

" Compile SFML Project WITH Audio
"
" term clang++ -std=c++17 -Lc:\SFML\lib -IC:\SFML\include -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system  % -o %.exe




