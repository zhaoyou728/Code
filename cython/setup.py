from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import platform 
import sys


version = int(platform.python_version()[0])
if version == 2:
    from imp import reload
    reload(sys)
    sys.setdefaultencoding('utf8')
    
ext = cythonize(Extension(name = 'copllp',sources = ["copllp.pyx","c/copl.c",
	"c/coplbasi.c","c/coplcrus.c","c/copldens.c","c/coplhash.c","c/coplhomo.c","c/coplmemo.c",
	"c/coplmpsf.c","c/coplopti.c","c/coplpara.c","c/coplpres.c","c/coplpsub.c","c/coplshut.c",
	"c/coplouta.c","c/coplstac.c",
	"c/Dmatrix.c","c/Dmemory.c","c/Dmmdpro.c","c/Dnumfac.c","c/Dprique.c","c/Dvector.c",
	"c/Xbasics.c","c/Xclean.c","c/Xcross.c","c/Xdual.c","c/Xlubasi.c","c/Xlufact.c",
	"c/Xlusolv.c","c/Xprimal.c","c/Xsimplx.c","c/Zldpnt.c",
	"c/coplrepo.c","c/coplpost.c"]
    ))
    
setup(
    name="COPLLP",
    version="1.0.0",
    author="Daniel",
    author_email = '1569698367@qq.com',
    description = 'Used to solve linear problem',
    url="https://bitbucket.org/account/signin/?next=/shufe_opt/coplp",
    license="SUFE",
    requires=["numpy","scipy"],
    ext_modules=ext,
),
