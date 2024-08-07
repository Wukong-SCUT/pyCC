# DG2

The FEs needed by DG2： $\frac{n^2+n+2}{2}$



As the improved version of the DG，DG2 has the following major changes over its predecessor:

- Efficiency: Lower computational cost
- Accuracy: Higher interaction detection accuracy
- Parameter-free



## The main improvement skills of DG2

### The systematic selection of sample points

<img src="C:\Users\悟空\AppData\Roaming\Typora\typora-user-images\image-20240807142935163.png" alt="image-20240807142935163" style="zoom: 67%;" />

The core of interaction detection in DG is shown in the picture above. We can see that if we want to check the interaction between $x_1$ and $x_2$, we need 4 FEs ( $f(p_1)$, $f(p_2)$, $f(p_3)$, $f(p_4)$ ). So, for an $n$-dimensional function, the total FEs is $4 \cdot\binom{n}{2} = 2 n(n-1)$.

But by systematic selection of sample points, the total number of FEs can be significantly reduced.

<img src="C:\Users\悟空\AppData\Roaming\Typora\typora-user-images\image-20240807144220545.png" alt="image-20240807144220545" style="zoom:80%;" />

An simple example of the systematic selection of sample points is shown in the picture above. if we want to check the interaction of $x_1$, $x_2$ and $x_3$, we only 7 FEs : $f(a, b, c)$ , $f\left(a^{\prime}, b, c\right)$ , $f\left(a,b^{\prime},c\right)$ , $f\left(a,b,c^{\prime}\right)$ , $f(a^{\prime},b^{\prime},c)$ , $f(a^{\prime},b,c^{\prime})$ , $f(a,b^{\prime},c^{\prime})$

```math
\begin{array}{l}
x_{1} \leftrightarrow x_{2}: \Delta^{(1)}=f\left(a^{\prime}, b, c\right)-f(a, b, c), \Delta^{(2)}=f\left(a^{\prime}, b^{\prime}, c\right)-f\left(a, b^{\prime}, c\right) \\
x_{1} \leftrightarrow x_{3}: \Delta^{(1)}=f\left(a^{\prime}, b, c\right)-f(a, b, c), \Delta^{(2)}=f\left(a^{\prime}, b, c^{\prime}\right)-f\left(a, b, c^{\prime}\right) \\
x_{2} \leftrightarrow x_{3}: \Delta^{(1)}=f\left(a, b^{\prime}, c\right)-f(a, b, c), \Delta^{(2)}=f\left(a, b^{\prime}, c^{\prime}\right)-f\left(a, b, c^{\prime}\right)
\end{array}
```

However, we need $\left.2 n(n-1)\right|_{n=3}=12$ FEs in the interaction detection in DG.

Why? Because the redundant evaluations:
```math
\left\{\begin{array}{ll}
\frac{n(n-1)}{2}-1 & : \text { redundant evaluations of }\left(x_{1}, \ldots, x_{n}\right) \\
n(n-2) & : \text { redundant evaluations of }\left(\ldots, x_{i}^{\prime}, \ldots\right)
\end{array}\right.
```
It is same in the simple example above.  

Then the total of FEs: $2n(n-1)-(\frac{n(n-1)}{2}-1)-n(n-2) = \frac{n(n+1)}{2}+1$

The implementation of the process that was described above:

<img src="C:\Users\悟空\AppData\Roaming\Typora\typora-user-images\image-20240807160502165.png" alt="image-20240807160502165" style="zoom:50%;" />

### Adaptive Threshold

<img src="C:\Users\悟空\AppData\Roaming\Typora\typora-user-images\image-20240807205006533.png" alt="image-20240807205006533" style="zoom:67%;" />

DG needs to set the threshold value ($\epsilon$) to detect interacting variables. Why we need to set a threshold instead of using 0 ? Because the floating-point operations incur computational roundoff errors. So we should find the least upper bound and greatest lower bound of the computational roundoff errors.
```math
\gamma_{k} := \frac{k \mu_{\mathrm{M}}}{1-k \mu_{\mathrm{M}}}
```

```math
e_{\text {inf }}=\gamma_{2}\left(|f(\mathbf{x})|+\left|f\left(\mathbf{y}^{\prime}\right)\right|+|f(\mathbf{y})|+\left|f\left(\mathbf{x}^{\prime}\right)\right|\right)
```

```math
e_{\text {sup }}=\gamma_{\sqrt{n}} \max \left\{f(\mathbf{x}), f\left(\mathbf{x}^{\prime}\right), f(\mathbf{y}), f\left(\mathbf{y}^{\prime}\right)\right\}
```

Then we know the the least upper bound $e_{\text {inf }}$ and greatest lower bound $e_{\text {sup }}$, We need to automatically set thresholds based on them.
```math
\epsilon=\frac{\eta_{0}}{\eta_{0}+\eta_{1}} e_{\text {inf }}+\frac{\eta_{1}}{\eta_{0}+\eta_{1}} e_{\text {sup }}
```
$\eta_{0}$ is the number of entries in $\Lambda$ which are less than $e_{inf}$, and $\eta_{1}$ is the number of entries in $\Lambda$ which are greater than $e_{sup}$. Why Equation is like this is because it represents which side has more reliable values, and the more reliable values should be, the closer they should be.

The implementation of the process that was described above:

<img src="C:\Users\悟空\AppData\Roaming\Typora\typora-user-images\image-20240807203843184.png" alt="image-20240807203843184" style="zoom: 50%;" />
