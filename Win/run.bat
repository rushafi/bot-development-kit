@ECHO off
SET args=0
FOR %%x IN (%*) DO SET /A args+=1
g++ newBot.cpp -o newBot.exe
g++ newHeader.cpp -o newHeader.exe
IF [%1] == [-c] (
	DEL /q obj\post\*.o
	DEL /q snake.exe
	DEL /q simulation\*.txt
) ELSE IF [%1] == [-n] (
	newBot.exe %2
) ELSE IF [%1] == [-d] (
	newHeader.exe
) ELSE IF [%1] == [-map] (
	IF %args% GTR 2 (
		IF %args% == 3 (
			newHeader.exe %3
			cd obj\post
			g++ -c ..\..\src\*.cpp
			cd ..\..
			g++ obj\post\*.o -o snake.exe
			snake.exe arena\%2
			cd simulation
			flashplayer.exe Snake.swf 
			cd ..
		) ELSE (
			newHeader.exe %3 %4
			cd obj\post
			g++ -c ..\..\src\*.cpp
			cd ..\..
			g++ obj\post\*.o -o snake.exe
			snake.exe arena\%2
			cd simulation
			flashplayer.exe Snake.swf 
			cd ..
		)
	) ELSE (
		cd obj\post
		g++ -c ..\..\src\*.cpp
		cd ..\..
		g++ obj\post\*.o -o snake.exe
		snake.exe arena\%2
		cd simulation
		flashplayer.exe Snake.swf 
		cd ..
	)
) ELSE (
	cd obj\post\
	g++ -c ..\..\src\*.cpp
	cd ..\..
	g++ obj\post\*.o -o snake.exe
	snake.exe arena\1
	cd simulation
	flashplayer.exe Snake.swf 
	cd ..
	pause
)
