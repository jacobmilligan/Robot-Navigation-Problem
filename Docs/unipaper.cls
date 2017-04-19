\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{unipaper}

\LoadClass[headings=standardclasses, abstract=on,10pt]{scrartcl}

\RequirePackage{pdfpages}
\RequirePackage{datetime}
\RequirePackage{hyperref}
\RequirePackage{fontspec}
\RequirePackage{amsmath,amsfonts,amsthm}
\RequirePackage[automark, headsepline]{scrlayer-scrpage}
\RequirePackage[style=authoryear,backend=biber]{biblatex}
\RequirePackage{etoolbox}
\RequirePackage[outputdir=tex_build]{minted}
\RequirePackage{listings}
\RequirePackage{tcolorbox}
\RequirePackage[titletoc,title]{appendix}

\tcbuselibrary{breakable,skins,minted}

\pagestyle{scrheadings}

\clearscrheadfoot
\ihead*{\pagemark}
\ohead{\headmark}

\definecolor{bluegray}{HTML}{265C83}
\definecolor{codebg}{HTML}{F6F8FA}
\definecolor{framecolor}{HTML}{DADADA}

\hypersetup {
	colorlinks	= true,
	urlcolor  	= bluegray,
	filecolor		= bluegray,
	linkcolor		= bluegray,
	citecolor		= bluegray
}

\usemintedstyle{vs}
\setminted{breaklines=true}
\setmonofont[Scale=0.7]{Menlo}

% Info commands
\newcommand{\@university}{}
\newcommand{\university}[1]{\renewcommand{\@university}{#1}}

\newcommand{\@unitcode}{}
\newcommand{\unitcode}[1]{\renewcommand{\@unitcode}{#1}}

\newcommand{\@unitname}{}
\newcommand{\unitname}[1]{\renewcommand{\@unitname}{#1}}

\newcommand{\@studentid}{}
\newcommand{\studentid}[1]{\renewcommand{\@studentid}{#1}}

\newcommand{\@crest}{}
\newcommand{\crest}[1]{\renewcommand{\@crest}{#1}}

\newcommand{\@semester}{}
\newcommand{\semester}[1]{\renewcommand{\@semester}{#1}}

% Section commands
\newif\ifsubtitle\subtitlefalse
\renewcommand{\@subtitle}{}
\renewcommand{\subtitle}[1]{\renewcommand{\@subtitle}{#1}\subtitletrue}

\renewcommand{\abstractname}{\Large Abstract}
\patchcmd\abstract{\normalsize}{}{}{}

% Environments
\newenvironment{acknowledgements}{
	\section*{\centerline{Acknowledgements}}
	\thispagestyle{empty}
}

\newenvironment{frontmatter}[1]{
	\section*{\centerline{#1}}
	\thispagestyle{empty}
}

\newtcbinputlisting{codeinput}[2]{
	listing file={#2},
	minted language={#1},
	minted options={breaklines},
	breakable,enhanced,listing only,
	colback=codebg,colframe=framecolor,
	boxrule=0.08em,
	arc=0.1em
}

\newtcbinputlisting{codeinputwithtitle}[3]{
	listing file={#2},
	minted language={#1},
	minted options={breaklines},
	breakable,enhanced,listing only,
	colback=codebg,colframe=framecolor,
	boxrule=0.08em,coltitle=black,
	arc=0.1em,title={#3}
}

\BeforeBeginEnvironment{minted}%
     {\begin{tcolorbox}[breakable=unlimited,colback=codebg, colframe=framecolor, boxrule=0.08em, arc=0.1em]}%
\AfterEndEnvironment{minted}
   {\end{tcolorbox}}%

% Define maketitle
\renewcommand{\maketitle}{
	\thispagestyle{empty}

	\begin{center}
	\vspace*{2em}
	\Huge \textbf{\@title} \par

	\ifsubtitle
		\huge \textit{\@subtitle} \par
	\fi

	\vfill
	\vspace{-5em}
	\@crest
	\vspace{-5em}
	\vfill

	\huge \textbf{\@author} \par
	\Large \@studentid \par
	\vspace{3em}

	\@university \par
	\textit{\@unitcode \ - \@unitname}
	\vspace{2em}
	\vfill

	\monthname[\the\month], \the\year, Semester \@semester

	\end{center}
	\clearpage
}

