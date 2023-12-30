<a name="readme-top"></a>

<br />
<div align="center">
  <a href="https://github.com/guinat/Projet_CY_Truck_preIng2_2023_2024">
    <img src="logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">CY Truck</h3>

  <p align="center">
    Coding the Future of Transport!
    <br />
    <a href="https://github.com/guinat/Projet_CY_Truck_preIng2_2023_2024"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/guinat/Projet_CY_Truck_preIng2_2023_2024">View Demo</a>
    ·
    <a href="https://github.com/guinat/Projet_CY_Truck_preIng2_2023_2024/issues">Report Bug</a>
    ·
    <a href="https://github.com/guinat/Projet_CY_Truck_preIng2_2023_2024/issues">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>

## About The Project

The CY Truck project, led by Eva Ansermin and Romuald Grignon, involves creating a program to manage the logistics of a national road transport company. This project addresses the challenge of manually processing large and varied logistics data. The program is designed to analyze a data file and generate graphs summarizing the company's activities.

<div align="left"> 
  <h4> Development of a Shell Script and a C Program  </h4>
    <p>The Shell script, along with a C program for performance operations, analyzes the data file and creates           graphs.
    </p>
    <h4> Data Management and Processing </h4>
    <p>The program manages a CSV file containing road trip data, including 'RouteID', 'StepID', 'Departures','Arrivals', 'Distance', and 'Driver Names'.
    </p>
  <h4> Graph Creation using GnuPlot </h4>
    <p> After processing the data, the Shell script uses GnuPlot to create graphs illustrating various aspects of       the data, such as drivers with the most trips, longest distances traveled, longest trips, and most       traversed cities.
    </p>
    <h4>Organization and Storage of Data and Results</h4>
    <p>Input data, programs, graphs, and intermediate files are organized into specific folders for better management.</p>
  <h4>Flexibility and Scalability</h4>
  <p>The project is designed to be scalable, with options for enhancement and adaptation to specific needs.</p>
  <br />
  The CY Truck project represents a robust and efficient IT solution for managing logistics   
  data in the road transport sector.
</div>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [![C][C]][C-url]
* [![Shell][Shell]][Shell-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Getting Started

This project requires several tools and packages to be installed on your system. Ensure you have the following prerequisites installed before proceeding with the project setup.

### Prerequisites

* GnuPlot is used for generating graphs from data. Install it via your system's package manager. For example, on    Ubuntu:
  ```sh
  sudo apt-get install gnuplot
  ```

* Make is a build automation tool that automatically builds executable programs and libraries. Install it as follows:
  ```sh
  sudo apt-get install make
  ```

* ImageMagick is a software suite to create, edit, compose, or convert bitmap images. It can be installed with:
  ```sh
  sudo apt-get install imagemagick
  ```
  
Ensure that all these tools are correctly installed on your system. They are essential for running and managing various aspects of the project, from data processing to image manipulation.

### Installation

* Clone the repo

   ```sh
   git clone https://github.com/guinat/Projet_CY_Truck_preIng2_2023_2024.git
   ```

* After performing a git clone of the repository, navigate to the project directory with the following command:

  ```sh
   cd Projet_CY_Truck_preIng2_2023_2024/
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage

This section guides you through the steps to execute and use the CY Truck program. The program is executed via a Shell script that processes a CSV file and generates various outputs based on the options provided.

<h3 align="left">Preparing the Data File</h3>

Ensure that you have the CSV file containing the road trip data prepared and ready for use. This file should include the following details, listed in order: '**RouteID**', '**StepID**', '**Departures**','**Arrivals**', '**Distance**', and '**Driver Names**'.

<h3 align="left">Running the Script</h3>

Before running the script, ensure that your main script has the necessary permissions to be executed. You can grant execute permission using the following command in your terminal

```sql
  chmod +x main.sh
```

To execute the program, use the following command format in your terminal. Replace **[path_to_csv_file]** with the actual path to your CSV file and **[option]** with the desired operation option.

  ```sql
  ./main.sh [path_to_csv_file] [option]
  ```

<h3 align="left">Understanding the Options</h3>

The **[option]** in the command represents various operations you can perform with the script. Here is the list of available options:

**-h**  : This option displays a help message explaining the available options for the script. It's useful for users who need guidance on how to use the script and what parameters to input.

**-d1** : This option is for processing and generating a horizontal histogram graph showing the top 10 drivers with the most trips. It sorts the drivers by the number of trips they have made in descending order and displays this information graphically.

**-d2** : When using this option, the script calculates the total distance traveled by each driver and generates a horizontal histogram graph. It focuses on the top 10 drivers who have covered the longest distances, sorted in descending order of distance traveled.

**-l**  : This option identifies the 10 longest trips based on total distance. It processes the data to sum up the distance for each trip and then generates a vertical histogram graph, sorting the results by trip identifier in ascending order.

**-t**  : When selected, this option counts the number of trips passing through each city and the number of times these cities are starting points of trips. It then creates a grouped histogram graph for the top 10 cities, sorted alphabetically, showing the total number of trips through each city and the number of times they are trip starting points.

**-s**  : This option is designed to gather statistics on the stages of each trip, such as minimum, maximum, and average distances. It creates a min-max-average curve graph, displaying these values for the top 50 trips, sorted by the difference between maximum and minimum distances in descending order.

Replace **[option]** with the specific operation you need to perform.
Each option is tailored to provide specific insights into the road trip data, making it easier to analyze and visualize different aspects of the dataset.

<h3 align="left">Viewing the Output</h3>

After running the script with your chosen option, the output such as graphs will be generated. These are typically saved in a designated output folder (images) and displayed on the screen.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[C]: https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white
[C-url]: https://devdocs.io/c/
[Shell]: https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white
[Shell-url]: https://www.gnu.org/software/bash/
