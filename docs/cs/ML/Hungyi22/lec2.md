**(Link)[https://www.bilibili.com/video/BV1Wv411h7kN?p=18]**

!!! note
    - Distinguish
        - Model bias: the needle isn't in the haystack,too small,inflexible
        - Optimization issue:  flexible enough,but if Deeper network < smaller network


## Proj 4 Scheme

### Problem 3 Implement the missing part of scheme_eval

```python
def scheme_eval(expr, env, _=None): # Optional third argument is ignored
    """Evaluate Scheme expression EXPR in Frame ENV.
        scheme_eval 在给定环境中求值一个 Scheme 表达式。
        scheme_eval 将评估重定向至在 scheme_forms.py 中找到的适当 do_?_form 函数
        scheme_apply 对某些参数应用一个过程。
    >>> expr = read_line('(+ 2 2)')
    >>> expr
    Pair('+', Pair(2, Pair(2, nil)))
    >>> scheme_eval(expr, create_global_frame())
    4
    """
    # 1. 处理原子符号 (Scheme 符号或自我评估的表达式)
    if scheme_symbolp(expr):
        return env.lookup(expr)  # 查找符号在环境中的值
    
    # 2. 处理自我评估的表达式
    elif self_evaluating(expr):
        return expr  # 直接返回表达式（例如数字、字符串等）

    # 3. 处理非原子表达式（即列表）
    if not scheme_listp(expr):
        raise SchemeError('malformed list: {0}'.format(repl_str(expr)))  # 如果不是列表，抛出错误
    
    first, rest = expr.first, expr.rest  # 获取表达式的第一个元素和其余部分

    # 4. 如果第一个元素是特殊形式（例如 `if`, `define` 等），使用相应的处理函数
    if scheme_symbolp(first) and first in scheme_forms.SPECIAL_FORMS:
        return scheme_forms.SPECIAL_FORMS[first](rest, env)  # 调用特殊形式的处理函数
    
    else:
        # 5. 一般的组合式，首先求值操作符，然后求值参数，最后应用操作符到参数
        # 假设我们有表达式 (+ 2 2)，
        # first = +，这时 procedure = scheme_eval(first, env) 会返回 `+` 操作符，
        # rest = (2 2)，这时 args = rest.map(lambda exp: scheme_eval(exp, env)) 会返回 [2, 2]，即两个数字 2。
        # 最后，scheme_apply(procedure, args, env) 会执行 `+` 操作符，传入参数 [2, 2]，结果为 4

        # BEGIN PROBLEM 3
        procedure = scheme_eval(first, env)  # 求值操作符
        args = rest.map(lambda exp: scheme_eval(exp, env))  # 求值所有参数
        return scheme_apply(procedure, args, env)  # 应用操作符到参数
        # END PROBLEM 3
```


核心速览

MVPaint是一种用于3D绘画的同步多视图扩散框架，能够生成高分辨率、无缝的纹理，并强调多视图一致性。

研究背景

·  研究问题：3D纹理生成是3D资产制作流程中的关键步骤，它增强了3D资产的视觉吸引力和多样性。尽管在文本到纹理（T 2T）生成方面取得了进展，但现有方法常常因为局部不连续性、多视图间不一致以及对UV展开结果的过度依赖而产生次优结果。
·  研究难点：在3D纹理生成中，确保多视图一致性是一个挑战，因为局部风格不连续性和大量接缝的存在。此外，生成多样化的纹理细节，避免过于平滑的纹理，同时实现高分辨率输出，以及开发不依赖UV展开结果的方法以实现稳健的自动化生成，都是当前研究中需要解决的问题。
·  文献综述：为了应对这些挑战，研究者们提出了各种方法，如利用2D扩散先验来指导生成过程，使用条件控制（例如深度）来产生更合适的纹理。TEXTure和Text 2Tex通过迭代渲染深度图来生成高质量图像。SyncMVD结合了多视图单步去噪和UV空间同步，但其重用的注意力过程仅限于附近视图，经常导致Janus问题。Paint 3D和Meta 3D TextureGen采用UV位置图进行UV修复和增强，但这些工具严重依赖连续的网格UV展开。因此，研究者们提出了MVPaint，这是一个粗到细的3D纹理生成框架，能够在减少对UV展开质量依赖的同时，生成高保真、无缝的3D纹理，并确保多视图一致性。

MVPaint框架

MVPaint框架主要包括三个关键模块：

1. 同步多视图生成（SMG）：通过使用具有交叉注意力和UV同步的多视图扩散模型，基于给定的纹理指令启动3D纹理生成，有效避免Janus问题，并在低分辨率下产生高度一致的多视图图像。
2. 空间感知3D修复（S 3I）：确保第一阶段未观察到的区域的完整3D纹理，通过考虑从网格表面均匀采样的3D点之间的空间关系来解决3D空间中的修复过程。
3. UV细化（UVR）模块：包括一系列在UV空间中定制的纹理增强操作。UVR首先使用超分辨率模块将UV图放大到2K分辨率，然后引入空间感知接缝平滑算法（SSA）来修正空间不连续的纹理，特别是修复由UV展开引起的接缝。

为了评估T 2T生成，研究者们建立了两个基准：Objaverse T 2T基准和GSO T 2T基准。Objaverse T 2T基准包括从Objaverse数据集中精选的1000个高质量3D网格，而GSO T 2T基准则利用GSO数据集中的所有1032个3D模型来评估T 2T模型的泛化能力。通过在这些基准上的广泛实验结果表明，MVPaint能够超越现有的最先进方法，显著减少失败的生成情况，如缺失区域、大不一致、过度平滑和Janus问题。

MVPaint框架

·  多视图同步生成（SMG）：MVPaint使用同步多视图生成（SMG）模型，该模型利用跨注意力机制和UV同步，基于给定的纹理指令初始化3D纹理生成，有效避免了Janus问题，确保了低分辨率下的多视图一致性。
·  空间感知3D修复（S 3I）：为了确保完整的3D纹理，特别是对于第一阶段未观察到的区域，提出了空间感知3D修复（S 3I）方法，通过考虑从网格表面均匀采样的3D点之间的空间关系来解决3D空间中的修复过程。
·  UV细化（UVR）模块：引入了UV细化（UVR）模块，包括一系列在UV空间中进行的纹理增强操作。UVR首先使用超分辨率模块将UV图上采样到2K分辨率，然后引入空间感知缝合算法（SSA）来修正空间不连续的纹理，特别是修复由UV展开引起的缝隙。

相关工作

·  多视图生成：从不同输入（如文本、图像和网格）生成一致的多视图图像，已成为一个关键研究领域，这使得创建在不同视角下外观一致的3D资产成为可能。
·  3D纹理生成：传统上依赖于手动或程序化技术，这些技术对于基本应用有效，但缺乏复杂性。随着全局优化技术的引入，可以生成更详细、更匹配3D模型几何形状的纹理。基于AI的3D纹理生成最初由生成对抗网络（GANs）主导，随后转向潜在扩散模型（LDM），其中Stable Diffusion等模型显示出有希望的结果。

实验

·  实施细节：使用MVDream作为T 2MV的基模型，并添加控制模块Tp进行训练。对于同步细化，选择SDXL作为I 2I细化D₁₂i的基础模型，部署了两个预训练的ControlNets，Tt和Tg。
·  文本指导的3D纹理生成：为了全面评估任意类型网格的文本到纹理（T 2T）生成，建立了两个评估基准：Objaverse T 2T基准和GSO T 2T基准。使用常见的生成指标：Fréchet Inception Distance (FID)、Kernel Inception Distance (KID)和CLIP得分来评估图像分布、质量和丰富度。
·  消融研究：为了验证SMG模块的有效性，进行了详细的消融研究，包括T 2MV扩散模型、多视图同步和几何感知细化。此外，还验证了3D修复和缝合操作的有效性。

应用

·  生成多样化的3D纹理：基于文本指令，MVPaint能够生成具有大变化的3D纹理。例如，对于单一独角兽模型，MVPaint能够生成38种不同的3D纹理。
·  纹理AI生成的3D网格：MVPaint独立于UV展开质量生成3D纹理，即使AI生成的3D网格包含轻微的瑕疵，也能生成高质量的纹理。

总体结论

·  MVPaint框架：MVPaint是一个综合框架，用于从文本生成3D纹理，包括三个关键阶段：同步多视图生成、3D空间纹理修复和UV细化。通过广泛的实验，MVPaint一致地生成高质量的3D纹理，超越了现有的最先进的纹理方法。
·  研究意义：MVPaint的提出，不仅解决了3D纹理生成中的一致性和无缝性问题，还减少了对UV展开质量的依赖，为未来3D纹理生成研究提供了重要的贡献。