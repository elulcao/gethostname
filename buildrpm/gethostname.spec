%if 0%{?with_debug}
	# https://bugzilla.redhat.com/show_bug.cgi?id=995136#c12
	%global _dwz_low_mem_die_limit 0
%else
	%global debug_package   %{nil}
%endif

%global _buildhost localhost.localdomain
%define _binaries_in_noarch_packages_terminate_build 0

Name:              gethostname
Version:           1.0.0
Release:           1%{?dist}
Summary:           Spoof gethostname system call
Group:		   System Environment/Libraries
BuildArch: 	   noarch
License:           Apache-2.0
URL:               https://github.com/elulcao/gethostname
Vendor:		   elulcao
Source0:           %{name}-%{version}.tar.bz2
BuildRequires:     gcc
Requires:          hostname

%description
Spoof gethostname system call

%prep
%setup -q -n %{name}-%{version}

%build
make build

%install
mkdir -p $RPM_BUILD_ROOT/%{_bindir} $RPM_BUILD_ROOT/%{_libdir}
make install BINDIR=$RPM_BUILD_ROOT/%{_bindir} LIBDIR=$RPM_BUILD_ROOT/%{_libdir}

%files
%license LICENSE
%defattr(-,root,root)
%attr(0755,root,root) %{_libdir}/lib%{name}.so.1

%changelog
* Thu Nov 18 2021 elulcao <elulcao@icloud.com> 1.0.0-1
- Initial version of the package
