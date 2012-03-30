Name:		Reaction
Version:	1.0
Release:	1%{?dist}
Summary:	Reaction is a port of the classic Action Quake 2 to a modified Quake 3 engine

Group:		Amusements/Games
License:	GPL
URL:		http://www.rq3.com
Source0:	http://www.rq3.com/download/Reaction-%{version}.tar.gz
Source1:	%{name}.desktop
Source2:	%{name}.png
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:	desktop-file-utils SDL-devel openal-soft-devel libvorbis-devel libjpeg-devel libcurl-devel zlib-devel speex-devel
Requires:	Reaction-data = %{version}

%description
Reaction was originally called Reaction Quake 3 which was a "total conversion mod" for Quake III Arena based on action and realism with a specific emphasis on action over realism. Reaction is a port of the classic Action Quake 2 (AQ2) mod. AQ2 still enjoyed great popularity in online gaming even 4 years after it was initially released and on an "obsolete" game engine as well. Many people attribute this lasting popularity to both the unique gameplay and the AQ2 community. At the time Reaction Quake 3 was first released, AQ2 was still more popular than any other Q3 realism mod and any other Quake 2 and Quake/QuakeWorld mods. Reaction Quake 3 aimed to bring the gameplay of AQ2 to a new, more modern game engine. This mod is made by AQ2 fans and players specifically for those who love the fast and furious AQ2 gameplay and also to hopefully expose a new generation of players to this unique gameplay.

%prep
%setup -q -n reaction


%build
make 

%install
mkdir -p $RPM_BUILD_ROOT%{_bindir}
install -m 0755 build/release-linux-*/Reactionded.* \
  $RPM_BUILD_ROOT%{_bindir}/Reactionded
install -m 0755 build/release-linux-*/Reaction.* \
  $RPM_BUILD_ROOT%{_bindir}/%{name}

mkdir -p $RPM_BUILD_ROOT%{_datadir}/applications
desktop-file-install --vendor fedora            \
  --dir $RPM_BUILD_ROOT%{_datadir}/applications \
  %{SOURCE1}
mkdir -p $RPM_BUILD_ROOT%{_datadir}/icons/hicolor/48x48/apps
install -p -m 644 %{SOURCE2} \
  $RPM_BUILD_ROOT%{_datadir}/icons/hicolor/48x48/apps


%clean
rm -rf $RPM_BUILD_ROOT

%post
touch --no-create %{_datadir}/icons/hicolor || :
if [ -x %{_bindir}/gtk-update-icon-cache ]; then
   %{_bindir}/gtk-update-icon-cache --quiet %{_datadir}/icons/hicolor || :
fi

%postun
touch --no-create %{_datadir}/icons/hicolor || :
if [ -x %{_bindir}/gtk-update-icon-cache ]; then
   %{_bindir}/gtk-update-icon-cache --quiet %{_datadir}/icons/hicolor || :
fi

%files
%defattr(-,root,root,-)
%doc ChangeLog COPYING.txt GPL
%{_bindir}/%{name}*
%{_bindir}/Reactionded
%{_datadir}/applications/fedora-%{name}.desktop
%{_datadir}/icons/hicolor/48x48/apps/%{name}.png


%changelog
* Fri Mar 30 2012 Richard Allen <ra@ra.is>
- Adding Icon and Desktop Icons
* Wed Mar 28 2012 Richard Allen <ra@ra.is>
- Initial version of the spec file for Reaction 1.0 based on the spec from tremulous
