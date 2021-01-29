<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/konradgthecoder/a1_primegaps">
    <img src="/images/matrix.jpg" alt="Logo" width="150" height="150">
  </a>

  <h3 align="center">PrimeGaps</h3>

  <p align="center">
    A C script which finds the largest gap between two consecutive integers in range [a, b].
    <br />
    <a href="https://github.com/konradgthecoder/a1_primegaps"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/konradgthecoder/a1_primegaps">View Demo</a>
    ·
    <a href="https://github.com/konradgthecoder/a1_primegaps/issues">Report Bug</a>
    ·
    <a href="https://github.com/konradgthecoder/a1_primegaps/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
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
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

This project was created for the purpose of an introduction to parallel computing. The advantage of multiple processors working in parallel on such a task as finding two consecutive integers between zero and one billion are clear compared to using just one single processor.

How it works:
* Each processor gets a range of numbers to work on
* This allows for more work to be done simultaneously
* One single processor can then decide the results after a data structure is populated

A list of commonly used resources that I find helpful are listed in the acknowledgements.

### Built With

This section should list any major frameworks that you built your project using. Leave any add-ons/plugins for the acknowledgements section. Here are a few examples.
* [C](https://en.wikipedia.org/wiki/C_(programming_language))
* [MPI](https://en.wikipedia.org/wiki/Message_Passing_Interface)
* [Béluga](https://docs.computecanada.ca/wiki/Béluga/en)



<!-- GETTING STARTED -->
## Getting Started

Here I'll provide some instructions that should work for supercomputer clusters enabled with git & MPI. 
Your cluster of choice will need to be able to compile & run C code.

### Prerequisites

Before you download/clone the repository you'll need to establish an ssh connection with your server of choice. In this case we used Béluga. Replace userid with your computecanada.ca username.
* ssh
  ```sh
  ssh -Y userid@beluga.computecanada.ca
  ```

### Installation

1. Create an SSH API key on your Béluga filesystem if you don't already have one.
2. Clone the repo
   ```sh
   git clone https://github.com/konradgthecoder/a1_primegaps.git
   ```
3. Compile the C code
   ```sh
   mpicc primegaps.c -o primegaps -lmpi
   ```
4. Submit your executable
   ```sh
   sbatch sample_submission_script.sh
   ```
5. See the resulting output
   ```sh
   cat slurm-jobId.out
   ```



<!-- USAGE EXAMPLES -->
## Usage

The default interval is [0, 1,000,000,000]. Feel free to change the interval in lines:

```c
int	a = 0;		/* Left interval boundary	*/
int	b = 1000000000;	/* Right interval boundary	*/
```

The default submission script uses one node & four tasks per node. Feel free to modify
the number of nodes and tasks in sample_submission_script.sh:

```bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
```

If you get an out of memory error, simply increase the memory per cpu:

```bash
#SBATCH --mem-per-cpu=256M
```

## Note

Ensure your b is divisible by the number of processors, p.



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/konradgthecoder/a1_primegaps/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Konrad Gapinski - [@konradgap](https://instagram.com/konradgap) - gapi3100@mylaurier.ca

Project Link: [https://github.com/konradgthecoder/a1_primegaps](https://github.com/konradgthecoder/a1_primegaps)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/konradgthecoder/a1_primegaps.svg?style=for-the-badge
[contributors-url]: https://github.com/konradgthecoder/a1_primegaps/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/konradgthecoder/a1_primegaps.svg?style=for-the-badge
[forks-url]: https://github.com/konradgthecoder/a1_primegaps/network/members
[stars-shield]: https://img.shields.io/github/stars/konradgthecoder/a1_primegaps.svg?style=for-the-badge
[stars-url]: https://github.com/konradgthecoder/a1_primegaps/stargazers
[issues-shield]: https://img.shields.io/github/issues/konradgthecoder/a1_primegaps.svg?style=for-the-badge
[issues-url]: https://github.com/konradgthecoder/a1_primegaps/issues
[license-shield]: https://img.shields.io/github/license/konradgthecoder/a1_primegaps.svg?style=for-the-badge
[license-url]: https://github.com/konradgthecoder/a1_primegaps/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/konradgapinski
[product-screenshot]: images/screenshot.png
