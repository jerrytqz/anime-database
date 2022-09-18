# anime-database

A database of anime complete with a built-in menu system using the command line

## Set Up and Run

```
apt install libncurses5-dev libncursesw5-dev
make
./main_run
```

## Database Format

The database reads in data from *database.txt*. Each entry in the file should be formatted like so:
```
The name of the anime 
The studio that created the anime 
Current number of episodes
Year the anime started airing
Whether the anime is still airing ("true" or "false")
Score of the anime from 1.00 to 10.00 inclusive (2 decimal places)

```

Note that the empty line at the end is part of the entry. Sample entries are provided in *database.txt*.  

## Features 

### List anime
- List by any field 
- List in ascending or descending order for numeric fields
- List in alphabetical or reverse alphabetical order for string fields

### Search for an anime
- Search by any field
- Search exactly or in a range for numeric fields 
- Search exactly or using keywords for string fields 

### Add an anime
- Overwrite anime with the same name 

### Remove anime
- Remove by any field 
- Remove by searching exactly or in a range for numeric fields
- Remove by searching exactly or using keywords for string fields 

## Images
![Home](images/Home.png "Home")
![List](images/List.png "List")
![Search](images/Search.png "Search")
![Add](images/Add.png "Add")
![Remove](images/Remove.png "Remove")
