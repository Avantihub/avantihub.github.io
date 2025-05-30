\documentclass[12pt]{article}
\usepackage[top=2cm, bottom=2cm, left=2.5cm, right=2.5cm]{geometry}
\usepackage{amsmath, amssymb, amsthm}
\usepackage{ctex}

\title{2023--2024学年线性代数II（H）期中}
\date{}
\author{任课教师：吴志祥 \quad 考试时长：120分钟}

\begin{document}

\maketitle
\thispagestyle{empty}

\begin{enumerate}
    \item 设$V$和$W$都是有限维线性空间，$T \in \mathcal{L}(V, W)$，证明$\text{im }T' = (\ker T)^0$。
    
    \item 设$T$是$\mathbb{F}^3$上的算子，它关于标准基的矩阵为
    $$
    \begin{pmatrix}
        2 & 2 & -2 \\
        2 & 4 & -3 \\
        -2 & -3 & 4
    \end{pmatrix}
,
    $$     求$\mathbb{F}^3$的一个由$T$的本征向量组成的规范正交基。          \item 求多项式$q \in \mathbb{R}[x]_3$，使得$\forall p \in \mathbb{R}[x]_3$，     $$
    \int_0^1 p(x)(\sin \pi x) \mathrm{d}x = \int_0^1 p(x)q(x) \mathrm{d}x.
    $$          \item 设$T \in \mathcal{L}(V)$，证明$T$是可逆的当且仅当存在唯一的等距同构$S \in \mathcal{L}(V)$使得$T = S\sqrt{T^*T}$。          \item 设$T \in \mathcal{L}(V, W)$，证明$T$是单射当且仅当$T^*$是满射。          \item 设$V$是实内积空间，$T$是$V$上的可逆线性变换，满足$\forall x, y \in V$，     $$
    \langle T(T(x)), y \rangle = \langle x, T(y) \rangle,
    $$     证明$T$是等距同构。          \item 设$T \in \mathcal{L}(V)$，对$u, v \in V$，定义     $$
    \langle u, v \rangle_T = \langle T(u), v \rangle,
    $$
    证明$\langle \cdot, \cdot \rangle_T$是$V$上的内积当且仅当$T$是关于原内积$\langle \cdot, \cdot \rangle$的可逆正算子。
    
    \item 设$T$是内积空间$V$上的正规算子，证明$\forall k \in \mathbb{Z}^+$，$\ker T^k = \ker T$。
    
    \item 判断下列命题的真伪，若它是真命题，请给出简单的证明；若它是伪命题，给出理由或举反例将它否定。
    
\begin{enumerate}
        \item $V$是线性空间，$V$的2个仿射子集的交也是$V$的仿射子集或者空集。
        
        \item $V$是有限维线性空间，$U$是$V$的真子空间，则一定存在非零的$f \in V'$，使得$f(U) = 0$。
        
        \item $V$是有限维线性空间，$U$是$V$的子空间，则$U = 0$当且仅当$U^0 = V'$。
        
        \item $\mathbb{R}^2$上存在一个内积，使得该内积确定的范数$\|(x, y)\| = \max\{|x|, |y|\}$。
    \end{enumerate}
\end{enumerate}

\end{document}