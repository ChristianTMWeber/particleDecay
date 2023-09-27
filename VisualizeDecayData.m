data = dlmread('ParticleDecayTest.txt');


norm = sqrt(sum(data(:,2:4).^2,2));

x=data(:,2)./norm;
y=data(:,3)./norm;
z=data(:,4)./norm;

figure(1); clf('reset');hold on;



plot3(x,y,z,'.');
axis([-1,1,-1,1,-1,1])
axis vis3d 